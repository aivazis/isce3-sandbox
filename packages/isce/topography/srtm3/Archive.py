# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce
# externals
import collections, functools, os


# the digital elevation model protocol
class Archive(isce.component, family='isce.topography.srtm', implements=isce.topography.archive):
    """
    Accessor for the SRTM data archive
    """

    # types
    from .Mosaic import Mosaic as mosaic
    from .Availability import Availability as availability


    # user configurable state
    region = isce.properties.array()
    region.doc = 'a cloud of (lat,lon) pairs that specifies of the region of interest'

    resolution = isce.properties.int(default=1)
    resolution.doc = 'the resolution of the data set in pixels per arc-second; either 1 or 3'

    team = isce.nexus.team()
    team.doc = 'the manager of the distributed pool of workers'

    pool = isce.properties.int(default=8)
    pool.doc = 'the maximum number of simultaneous connections to the remote data store'


    # protocol obligations
    @isce.export
    def sync(self, channel=None, dent=0):
        """
        Ensure that the availability map reflects the contents of the local store accurately
        """
        # get the map
        map = self.availabilityMap
        # build a mosaic over the entire globe
        globe = self.mosaic(region=[(-90,-180), (89,179)], resolution=self.resolution)
        # get the contents of the local store as a set of tile names
        contents = self.localstoreContents
        # do the sync
        map.sync(cache=contents, mosaic=globe)

        # make a channel
        channel = isce.journal.info(self.pyre_family()) if channel is None else channel
        # everything below is a report
        if not channel:
            # so skip it if the channel is not active
            return

        # compute the margin
        margin = '  '*dent
        # show me where the local store is
        channel.line('{}local cache: {.cache.uri}'.format(margin, self))
        # show me the name of the availability map
        channel.line('{}      map: {.uri.name}'.format(margin, map))
        # count the number of tiles that are present
        count = len(contents)
        # why not do it right...
        plural = '' if count == 1 else 's'
        # show me
        channel.line('{}  present: {} tile{}'.format(margin, count, plural))
        channel.line('{}    globe: {} tiles'.format(margin, len(globe)))
        # ask the map for a summary
        map.summary(channel=channel, dent=dent)

        # all done
        return


    @isce.export
    def plan(self, channel=None, dent=0):
        """
        Describe the work required to generate the specified DEM
        """
        # get my region
        region = self.region
        # build a mosaic that covers it
        mosaic = self.mosaic(region=self.region, resolution=self.resolution)
        # get the map
        map = self.availabilityMap
        # check the status of the tiles in the mosaic
        summary = self.checkAvailability(mosaic=mosaic)

        # make a channel
        channel = isce.journal.info(self.pyre_family()) if channel is None else channel
        # everything below is a report
        if not channel:
            # so skip it if the channel is not active
            return

        # compute the margin
        margin = '  '*dent
        # show me the region
        channel.line('{}region of interest: {}'.format(margin, region))
        # the layout of the mosaic
        channel.line('{}mosaic: {}x{} grid of tiles'.format(margin, *mosaic.shape))
        # where the local store is
        channel.line("{}cache: '{.cache.uri}'".format(margin, self))
        # the name of the availability map
        channel.line('{}map: {.uri.name}'.format(margin, map))

        # mark the section
        channel.line('{}tiles:'.format(margin))
        # show me the names of the needed tiles
        channel.line('{}    necessary: {}'.format(margin, ", ".join(tile.name for tile in mosaic)))
        # mark the section
        channel.line('{}status:'.format(margin))
        # and now the status piles
        for status in self.availability:
            # show me the code and the tiles
            channel.line('{}  {:>11}: {}'.format(
                margin,
                status.name,
                ", ".join(tile.name for tile in summary[status])))

        # all done
        return


    @isce.export
    def download(self, channel=None, dent=1, force=False, dry=False):
        """
        Retrieve the tiles necessary to cover the convex hull of my {region}
        """
        # build a mosaic that covers my region
        mosaic = self.mosaic(region=self.region, resolution=self.resolution)
        # check the status of its tiles
        summary = self.checkAvailability(mosaic=mosaic)
        # get my team manager
        team = self.team
        # adjust the desired number of workers
        team.size = self.pool
        # the node with my local tile archive
        cache = self.cache
        # and the tile availability map
        availability = self.availabilityMap
        # pull the crew type
        from .Downloader import Downloader
        # attach it
        team.crew = functools.partial(Downloader, map=availability, cache=cache)
        # assemble the work plan
        team.execute(workplan=set(mosaic))
        # and fetch the tiles
        team.run()

        print("NYI: task execution statistics")
        # all done
        return 0

        # make a timer
        timer = isce.executive.newTimer(name=self.pyre_family())
        # and a channel
        channel = isce.journal.info(self.pyre_family()) if channel is None else channel
        # compute the margin
        margin = '  '*dent

        # make a pile of workers
        workers = {}
        # check in
        channel.line('{}downloading:'.format(margin))
        # go through the tile URIs
        for tile in mosaic:
            # if the tile is locally cached
            if tile.status is self.availability.cached:
                # tell me
                channel.line('{}  skipping {tile.name}; {tile.status.name}'.format(
                    margin, tile=tile))
                # skip it
                continue
            # if the tile is known to not exist
            if tile.status is self.availability.unavailable:
                # skip it
                continue

            # for the tile uri
            uri = tile.filename

            # spawn a worker
            pid = os.fork()
            # add his id to the pile
            workers[pid] = uri
            # if this is the worker
            if pid == 0:
                # reset the timer
                timer.reset().start()
                # open the url
                response = urllib.request.urlopen(archive+uri)
                # grab the bytes
                contents = response.read()
                # create the destination file
                cache.write(name=uri, contents=contents, mode='wb')
                # update the tile status
                tile.status = self.availability.cached
                # update the map
                map.update(tile=tile)
                # show me
                channel.log('{}  got {!r} ({:.3f} sec)'.format(margin, uri, timer.stop().read()))
                # this worker is done
                raise SystemExit(0)

        # back at the ranch
        for _ in range(len(workers)):
            # wait for a worker to finish
            pid, status = os.wait()
            # show me
            channel.line('worker {}: tile {!r}, status {}'.format(pid, workers[pid], status))

        # all done
        return


    # implementation details
    @property
    def availabilityMap(self):
        """
        Fetch the SRTM tile availability map
        """
        # check whether i have done this before
        map = self._availabilityMap
        # and if i have
        if map is not None:
            # all done
            return map
        # otherwise, get the map
        map = self.loadAvailabilityMap()
        # cache it
        self._availabilityMap = map
        # and return it
        return map


    @property
    def localstoreContents(self):
        """
        Build a set of the tile names that are present in the local cache
        """
        # check whether I have done this before
        contents = self._localstoreContents
        # and if i have
        if contents is not None:
            # all done
            return contents
        # otherwise, get my cache
        cache = self.cache
        # build the pattern for the filenames with relevant tiles
        pattern = self._filenamePattern.format(srtm=self)
        # get the contents
        contents = set(match.group('name') for node, match in cache.find(pattern=pattern))
        # save them
        self._localstoreContents = contents
        # and return them
        return contents


    def loadAvailabilityMap(self):
        """
        Retrieve the tile availability map
        """
        # grab the factory
        from .AvailabilityMap import AvailabilityMap as map
        # form the uri to the map
        uri = self.cache.uri / self._availabilityMapTemplate.format(srtm=self)
        # build it and return it
        return map(uri=uri)


    def checkAvailability(self, mosaic):
        """
        Update the status of all tiles that are available in the {localstore}
        """
        # the summary dictionary: map status codes to a list of tiles
        summary = collections.defaultdict(list)
        # get the availability map
        map = self.availabilityMap

        # go through each of my tiles
        for tile in mosaic:
            # check it against the availability map
            status = map.getTileAvailability(tile)
            # place it in the right pile
            summary[status].append(tile)
        # all done
        return summary


    # private data
    cache = None # the filesystem node with my local store

    # storage for my properties
    _availabilityMap = None
    _localstoreContents = None

    # constants
    # the availability map filename
    _availabilityMapTemplate = 'srtmgl{srtm.resolution}.map'
    # the pattern for matching valid tile names in the local store
    _filenamePattern = '(?P<name>(N|S)\d{{2}}(E|W)\d{{3}})\.SRTMGL{srtm.resolution}.hgt.zip'


# end of file
