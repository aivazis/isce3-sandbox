# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce
# externals
import itertools, math, os, urllib.request


# the digital elevation model protocol
class SRTM(isce.component, family='isce.topography.srtm', implements=isce.topography.archive):
    """
    Accessor for the SRTM data archive
    """

    # types
    from .SRTMMosaic import SRTMMosaic as mosaic
    from .SRTMAvailability import SRTMAvailability as availability


    # user configurable state
    region = isce.properties.array()
    region.doc = 'a cloud of (lat,lon) pairs that specifies of the region of interest'

    resolution = isce.properties.int(default=1)
    resolution.doc = 'the resolution of the data set in pixels per arc-second; either 1 or 3'

    pool = isce.properties.int(default=8)
    pool.doc = 'the maximum number of simultaneous connections to the remote data store'


    # protocol obligations
    @isce.export
    def sync(self, channel=None, indent=1):
        """
        Ensure that the availability map reflects the contents of the local store accurately
        """
        # make a channel
        channel = isce.journal.info(self.pyre_family()) if channel is None else channel
        # compute the margin
        margin = '  '*indent
        # sign in
        channel.line('{}local cache: {.cache.uri}'.format(margin, self))

        # get the map
        map = self.availabilityMap
        # show me
        channel.line('{}      map: {.uri.name}'.format(margin, map))

        # get the contents of the local store as a set of tile names
        contents = self.localstoreContents
        # show me
        channel.line('{}   cached: {} tiles'.format(margin, len(contents)))

        # build a mosaic over the entire globe
        globe = self.mosaic(region=[(-90,-180), (90,180)], resolution=self.resolution)
        # show me
        channel.line('{}    globe: {} tiles'.format(margin, len(globe)))

        # do the sync
        map.sync(cache=contents, mosaic=globe, channel=channel)
        # ask for a summary
        map.summary(channel=channel)

        # all done
        return


    @isce.export
    def plan(self, channel=None):
        """
        Describe the work required to generate the specified DEM
        """
        # make a channel
        channel = isce.journal.info(self.pyre_family()) if channel is None else channel
        # sign in
        channel.line('cache:')
        channel.line('\n'.join(self.cache.dump(indent=2)))

        # get my region
        region = self.region
        # make some space
        channel.line('region of interest: {}'.format(region))

        # build a mosaic that covers my region
        mosaic = self.mosaic(region=self.region, resolution=self.resolution)
        # check the status of its tiles
        self.checkAvailability(mosaic=mosaic)

        # separate the tiles into two categories: the ones we have
        cached = {}
        # and the ones we need
        get = {}

        # go through the tiles
        for tile in mosaic:
            # get the tile name
            name = tile.name
            # form the filename
            filename = self.filename(tile=tile)
            # check whether the file is present in the cache
            if tile.isCached:
                # add to the pile of tiles we already have
                cached[filename] = name
            # otherwise
            else:
                # add it to the pile of tiles we have to download
                get[filename] = name

        # show me
        channel.line('  necessary:')
        channel.line('    {}'.format(", ".join(tile.name for tile in mosaic)))
        channel.line('  cached:')
        channel.line('    {}'.format(", ".join(cached.keys())))
        channel.line('  download:')
        channel.line('    {}'.format(", ".join(get.keys())))

        # flush
        channel.log()

        # all done
        return


    @isce.export
    def download(self, force=False, dry=False):
        """
        Retrieve the tiles necessary to cover the convex hull of my {region}
        """
        # make a timer
        timer = isce.executive.newTimer(name='isce.dem.download')
        # and a channel
        channel = isce.journal.info(name='isce.dem')

        # build a mosaic that covers my region
        mosaic = self.mosaic(region=self.region, resolution=self.resolution)
        # check the status of its tiles
        mosaic.checkAvailability(mosaic=mosaic)

        # build the archive uri
        archive = self.srtm.format(resolution)
        # make a pile of workers
        workers = {}
        # go through the tile URIs
        for uri in uris:
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
                content = response.read()
                # open the destination file
                tile = open(uri, 'wb')
                # save
                tile.write(content)
                # show me
                channel.log('got {!r} ({:.3f} sec)'.format(uri, timer.stop().read()))
                # this worker is done
                raise SystemExit(0)

        # back at the ranch
        for _ in range(len(workers)):
            # wait for a worker to finish
            pid, status = os.wait()
            # show me
            channel.line('worker {}: tile {!r}, status {}'.format(pid, workers[pid], status))
        # when they are all done, flush
        channel.log()

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
        # otherwise, form the uri to the map
        uri = self.cache.uri / self._availabilityMapTemplate.format(srtm=self)
        # grab the factory
        from .SRTMAvailabilityMap import SRTMAvailabilityMap as factory
        # build it
        map = factory(uri)
        # and return it
        return map


    def checkAvailability(self, mosaic):
        """
        Update the status of all tiles that are available in the {localstore}
        """
        # grab the local store
        cache = self.cache
        # get the availability map
        map = self.availabilityMap

        # go through each of my tiles
        for tile in mosaic:
            # if the filename is present in the localstore
            if self.filename(tile=tile) in cache:
                # mark the tile as locally cached
                tile.isCached = True
        # all done
        return


    def filename(self, tile):
        """
        The canonical name for the file that contains the tile grid
        """
        # easy...
        return self._filenameTemplate.format(srtm=self, tile=tile)


    def uriUSGS(self, tile):
        """
        Build the address for this tile at the USGS data store
        """
        # easy...
        return self._usgs.format(self)


    # private data
    cache = None # the filesystem node with my local store

    # storage for my properties
    _availabilityMap = None
    _localstoreContents = None

    # constants
    # the availability map filename
    _availabilityMapTemplate = 'srtmgl{srtm.resolution}.map'
    # the tile URI template: tile name and resolution
    _filenameTemplate = "{tile.name}.SRTMGL{tile.resolution}.hgt.zip"
    # the pattern for matching valid tile names in the local store
    _filenamePattern = '(?P<name>(N|S)\d{{2}}(E|W)\d{{3}})\.SRTMGL{srtm.resolution}.hgt.zip'
    # the template for the URI of the datastore at the USGS
    _usgs = 'http://e4ftl01.cr.usgs.gov/SRTM/SRTMGL{tile.resolution}.003/2000.02.11/'


# end of file
