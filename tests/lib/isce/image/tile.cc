// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// exercise tile construction:
//   verify that all the parts are accessible through the public headers
//   verify constructor signatures
//   assemble a tile
//   verify it can compute its size correctly

// portability
#include <portinfo>
// support
#include <isce/image.h>

// entry point
int main() {

    // shape
    isce::image::shape_t shape = {4,8,3};
    // the interleaving
    isce::image::layout_t layout = {isce::image::layout::line};
    // the index
    isce::image::index_t index = {2,3,2};
    // make a tile
    isce::image::tile_t tile = {shape, layout};

    // check the tile size calculation
    if (tile.pixels() != 4*8*3) {
        // make a firewall channel so we can report errors
        pyre::journal::firewall_t firewall("isce.image.tile");
        // complain
        firewall
            << pyre::journal::at(__HERE__)
            << "tile sizing error: " << tile.pixels() << " != " << 4*8*3
            << pyre::journal::endl;
        // bail
        return 1;
    }

    // make a debug channel
    pyre::journal::debug_t debug("isce.image.tile");
    // and display information about the tile layout
    debug
        << pyre::journal::at(__HERE__)
        << "shape  : (" << shape[0] << ", " << shape[1] << ", " << shape[2] << ")"
        << pyre::journal::newline
        << "layout : (" << layout[0] << ", " << layout[1] << ", " << layout[2] << ")"
        << pyre::journal::newline
        << "index  : (" << index[0] << ", " << index[1] << ", " << index[2] << ")"
        << pyre::journal::newline
        << "offset: " << tile[index]
        << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
