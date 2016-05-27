// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// exercise grid layout construction:
//   verify that all the parts are accessible through the public headers
//   verify constructor signatures
//   assemble a layout
//   verify it can be iterated

// portability
#include <portinfo>
// support
#include <isce/grid.h>

// entry point
int main() {
    // create a shortcut to my target tile type
    typedef isce::grid::tile_t<4> tile_t;

    // make a layout
    tile_t::layout_t layout {3u, 2u, 1u, 0u};
    // make a shape
    tile_t::shape_t shape {2u, 3u, 4u, 5u};
    // make a tile
    tile_t tile {shape, layout};

    // make a channel
    pyre::journal::info_t channel("isce.grid");

    // display information about the tile layout
    channel << pyre::journal::at(__HERE__);

    // show me the shape
    channel << "shape: (";
    for (auto sz : shape) {
        channel << " " << sz;
    }
    channel << " )" << pyre::journal::endl;

    // show me the layout
    channel << "layout: (";
    for (auto sz : layout) {
        channel << " " << sz;
    }
    channel << " )" << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
