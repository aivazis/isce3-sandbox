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

    # user configurable state
    cache = isce.properties.path()
    cache.doc = 'the path to the local cache of SRTM tiles'

    region = isce.properties.array()
    region.doc = 'the specification of the region of interest'

    hires = isce.properties.bool(default=True)
    hires.doc = 'select the model resolution'


    # protocol obligations
    @isce.export
    def plan(self):
        """
        Describe the work required to generate the specified DEM
        """
        # build the uri to my tile cache
        uri = self.cache / 'srtm'
        # get the application private filesystem
        pfs = self.pyre_application.pfs

        self.pyre_application.info.log('\n'.join(pfs.dump()))

        # attempt to
        try:
            # get the folder with the cached SRTM tiles
            cache = pfs[uri]
        # if it's not there
        except pfs.NotFoundError:
            # for the path to the srtm archive
            path = pfs[self.cache].uri / 'srtm'
            # ask for the folder to get make
            # path.mkdir('srtm')
            # refresh the filesystem view
            pfs[self.cache].discover(levels=1)
            # try again
            cache = pfs[uri]

        print(cache)


        # build the mosaic that covers the region
        mosaic = self.mosaic()
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

        # build a mosaic that covers my {region}
        mosaic = self.mosaic()
        # assemble their names
        names = self.tileNames(mosaic)
        # build the pile of tile URIs and return them to the caller
        uris = self.tileURIs(names)

        # convert the resolution setting
        resolution = 1 if self.hires else 3
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


    # convenience interface
    def uris(self):
        """
        Build a sequence of {uri}s that point to the tiles that cover my region
        """
        # build a mosaic that covers my {region}
        mosaic = self.mosaic()
        # assemble their names
        names = self.tileNames(mosaic)
        # build the pile of tile URIs and return them to the caller
        return self.tileURIs(names)


    # implementation details
    def mosaic(self):
        """
        Build a mosaic of SRTM tiles that cover the bounding box of the points in my {region} of
        interest
        """
        # get the region of interest
        region = self.region
        # if the user has not specified one
        if not region:
            # the mosaic is empty
            return []

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


    def tileNames(self, mosaic):
        """
        Given a sequence of (lat, lon) pairs, return a sequence of SRTM tile names
        """
        # go through each tile
        for tile in mosaic:
            # unpack
            lat, lon = tile
            # build the name of the tile; numeric fields are zero padded to three digits
            name = '{}{:02}{}{:03}'.format(
                "N" if lat >=0 else "S", abs(lat),
                "E" if lon >= 0 else "W", abs(lon))
            # hand the name to the caller
            yield name

        # all done
        return


    def tileURIs(self, names):
        """
        Build a sequence of the tile URIs from their names
        """
        # grab the tile template
        tile = self.tile
        # decide whether we are looking for the low or high resolution images
        resolution = 1 if self.hires else 3
        # go through each name
        for name in names:
            # form the uri and hand itoff
            yield tile.format(name, resolution)

        # all done
        return


    # constants
    # the template for the URI of the datastore
    srtm = 'http://e4ftl01.cr.usgs.gov/SRTM/SRTMGL{0}.003/2000.02.11/'
    # the tile URI template: tile name and resolution
    tile = '{0}.SRTMGL{1}.hgt.zip'


# end of file
