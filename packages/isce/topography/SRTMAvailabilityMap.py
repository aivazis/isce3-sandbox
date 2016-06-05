# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# the tile availability mpa
class SRTMAvailabilityMap:
    """
    The tile availability map
    """

    # types
    from .SRTMAvailability import SRTMAvailability as availability


    # interface
    def check(self, tile):
        """
        Check the availability of the given tile
        """
        # get its location
        index = tile.point
        # get the status from my map
        value = isce.extensions.isce.srtmAvailabilityMapGet(self.map, index)
        # convert it into an availability code and return it
        return tuple(self.availability)[value]


    def mark(self, tile, status):
        """
        Adjust the status of the given tile
        """
        # get its location
        index = tile.point
        # get the status value
        value = status.value
        # set the status in my map and return it
        return isce.extensions.isce.srtmAvailabilityMapSet(self.map, index, status.value)


    # meta-methods
    def __init__(self, uri, **kwds):
        # chain up
        super().__init__(**kwds)
        # save my path
        self.uri = uri
        # make the capsule
        self.map = isce.extensions.isce.srtmAvailabilityMap(str(uri))
        # all done
        return


# end of file
