// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// with a line interleaved tile
//   visit it in its native packing order
//   verify that the offsets are computed correctly
//   verify that the offsets map back to their index correctly

// portability adjustments
#include <portinfo>
// support
#include <isce/image.h>

// entry point
int main() {
    // shape
    isce::image::shape_t shape {4,8,3};
    // the interleaving
    isce::image::layout_t layout {isce::image::layout::pixel};
    // make a tile
    isce::image::tile_t tile {shape, layout};

    // specify the slice region
    isce::image::index_t begin {1,1,0};
    isce::image::index_t end {tile.shape()};

    // make a channel
    pyre::journal::debug_t channel("isce.image.tile");
    // if the channel is not active
    if (!channel) {
        // we are done
        return 0;
    }

    // otherwise, sign in
    channel << pyre::journal::at(__HERE__);

    // loop over the slice in packing order
    for (auto index : tile.slice(begin, end)) {
        // get the offset of the pixel at this index
        auto pixel { tile[index] };
        // show me
        channel
            << "(" << index[0] << "," << index[1] << "," << index[2] << ")"
            << " -> "
            << pixel
            << pyre::journal::newline;
    }
    // flush
    channel << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
