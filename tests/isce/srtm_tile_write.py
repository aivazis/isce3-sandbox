#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

"""
Download and make a local copy of an available SRTM tile
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

    # get the filesrver
    fs = isce.executive.fileserver
    # get the cwd
    cwd = fs[fs.STARTUP_DIR]

    # cache the compressed stream
    tile.write(cache=cwd, contents=contents)

    # refresh the filesystem node
    cwd.discover(levels=1)
    # verify the file is there
    assert tile.filename in cwd.contents

    # all done
    return


# main
if __name__ == "__main__":
    test()

# end of file
