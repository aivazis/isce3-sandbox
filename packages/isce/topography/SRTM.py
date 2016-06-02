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

    # user configurable state
    region = isce.properties.array()
    region.doc = 'a cloud of (lat,lon) pairs that specifies of the region of interest'

    hires = isce.properties.bool(default=True)
    hires.doc = 'select the model resolution'

    pool = isce.properties.int(default=8)
    pool.doc = 'the maximum number of simultaneous connections to the remote data store'



    # protocol obligations
    @isce.export
    def plan(self, channel=None):
        """
        Describe the work required to generate the specified DEM
        """
        # get my data store
        cache = self.cache
        # make a channel
        channel = isce.journal.info(self.pyre_family()) if channel is None else channel
        # sign in
        channel.line('cache:')
        channel.line('\n'.join(cache.dump(indent=2)))

        # get my region
        region = self.region
        # make some space
        channel.line('region of interest: {}'.format(region))

        # build a mosaic that covers my region
        mosaic = self.mosaic(region=self.region, hires=self.hires)
        # check the status of its tiles
        mosaic.checkAvailability(localstore=self.cache)

        # separate the tiles into two categories: the ones we have
        cached = {}
        # and the ones we need
        get = {}

        # go through the tiles
        for tile in mosaic:
            # check whether the file is present in the cache
            if tile.isCached:
                # add to the pile of tiles we already have
                cached[tile.filename] = tile.name
            # otherwise
            else:
                # add it to the pile of tiles we have to download
                get[tile.filename] = tile.name

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
        mosaic = self.mosaic(region=self.region, hires=self.hires)
        # check the status of its tiles
        mosaic.checkAvailability(localstore=self.cache)

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
    def _mosaic(self):
        """
        Build a mosaic of SRTM tiles that cover the bounding box of the points in my {region} of
        interest
        """
        # get the cloud of (lat, lon) pairs that define the region of interest
        region = self.region
        # make a mosaic
        mosaic = self.srtmMosaic(region=region)
        # all done
        return mosaic

        # otherwise, compute the north-south and east-west ranges that cover all the points in
        # my region; this is accomplished by finding the smallest and largest coördinate along
        # each axis; in order to handle negative numbers correctly, we use {math.floor} to
        # compute the integer part; we add one to the upper limits so that we can form the
        # sequence of values using {range}
        limits = tuple((math.floor(min(axis)), math.floor(max(axis))+1) for axis in zip(*region))
        # the limits form a grid whose shape is given by
        shape = tuple(high - low for low, high in limits)
        # and whose contents are all pairs of values in the range of each axis
        contents = itertools.product(*(range(*axis) for axis in limits))
        # build the grid
        mosaic = isce.geometry.grid(shape=shape)
        # populate it
        mosaic.extend(contents)
        # and return it
        return mosaic


    # private data
    cache = None


# end of file
