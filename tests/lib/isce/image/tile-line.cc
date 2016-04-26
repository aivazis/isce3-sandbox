// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//


// portability adjustments
#include <portinfo>
// externals
#include <iostream>

// support
#include <isce/image.h>

// entry point
int main() {
    // shape
    isce::image::shape_t shape = {4,8,3};
    // the interleaving
    isce::image::layout_t layout = {isce::image::layout::line};
    // make a tile
    isce::image::tile_t tile = {shape, layout};

    // initialize the offset
    size_t offset = 0;

    // loop over the tile in packing order
    for (auto index : tile) {
        // get the offset of the pixel at this index
        size_t pixel = tile[index];
        // verify it has the expected value
        if (offset != pixel) {
            // open a channel
            pyre::journal::firewall_t firewall("isce.image.bounds");
            // complain
            firewall
                << pyre::journal::at(__HERE__)
                << "offset error: " << offset << " != " << pixel
                << pyre::journal::endl;
            // and bail
            return 1;
        }
        // update the counter
        offset++;
    }

    // all done
    return 0;
}

// end of file
