# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# externals
import itertools, math
# support
import isce

# declaration
class SRTMMosaic(list):
    """
    A grid of SRTM tiles
    """

    # types
    from .SRTMTile import SRTMTile as tile


    # interface
    def checkAvailability(self, localstore):
        """
        Update the status of all tiles that are available in the {localstore}
        """
        # go through each of my tiles
        for tile in self:
            # if the filename is present in the localstore
            if tile.filename in localstore:
                # mark the tile as locally cached
                tile.isCached = True
        # all done
        return


    # meta-methods
    def __init__(self, region=[], hires=True, **kwds):
        """
        Create a grid of SRTM tiles that cover the bounding box of the {region} of interest

          parameters:
            region: a cloud of (lat, lon) pairs
        """
        # chain up
        super().__init__(**kwds)

        # figure out the region of interest
        self.cover(region=region, hires=hires)

        # all done
        return


    def __getitem__(self, point):
        """
        Return the tile that contains the (lat, lon) pair in {point}
        """
        # unpack the {point} and convert it into a tile spec
        lat, lon = map(math.floor, point)

        # my NW corner tile is at grid (0,0); get its (lat, lon)
        latNW, lonNW = self.nw
        # my shape
        rows, cols = self.shape

        # form the grid index
        row, col = (latNW - lat), (lon - lonNW)

        # check the latitude
        if row < 0 or row >= rows:
            # complain
            raise ValueError('latitude {} not in this mosaic'.format(lat))
        # check the longitude
        if col < 0 or col >= cols:
            # complain
            raise ValueError('longitude {} not in this mosaic'.format(lon))

        # convert the index into an offset
        offset = row * cols + col
        # and fetch the tile
        return super().__getitem__(offset)


    # implementation details
    def cover(self, region, hires):
        """
        Make sure this mosaic covers the region of interest
        """
        # if this is an empty region
        if not region:
            # give me a trivial shape
            self.shape = (0,0)
            # and reset my NW corner
            self.nw = (None, None)
            # all done
            return

        # we line up the grid in "book order": NW to SE, with the first row W to E, which means
        # that we must treat lats and lons differently; so unpack them
        lats, lons = zip(*region)

        # the northernmost latitude
        latN = math.floor(max(lats))
        # the southernmost latitude
        latS = math.floor(min(lats))
        # the easternmost longitude
        lonE = math.floor(max(lons))
        # the westernmost longitude
        lonW = math.floor(min(lons))

        # save my NW corner
        self.nw = (latN, lonW)
        # set up my shape
        self.shape = (latN - latS + 1, lonE - lonW + 1)

        # build the grid
        self.extend(
            # by adding tiles
             self.tile(point=point, hires=hires)
            # at the specified point
            for point in itertools.product(range(latN, latS-1, -1), range(lonW, lonE+1)))

        # all done
        return


    # private data
    # the (lat, lon) of the tile at the NW corner of the mosaic
    nw = None
    # the shape of the mosaic
    shape = None


# end of file
