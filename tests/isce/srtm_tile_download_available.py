#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

"""
Download an SRTM tile that is known to be available
"""

def test():
    # get the module
    import isce.topography.srtm3
    # build a tile
    tile = isce.topography.srtm3.tile(point=(34,-118))
    # get the data
    contents = tile.download()
    # check that the tile is available
    assert tile.status is tile.availability.available
    # decompress
    dem = tile.decompress(contents=contents)
    # verify that the contents are the right size
    assert len(dem) == 2*3601*3601

    # all done
    return


# main
if __name__ == "__main__":
    test()

# end of file
