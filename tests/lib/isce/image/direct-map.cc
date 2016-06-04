// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// given a file named "image.dat" in the current directory, use the low level interface to map
// it into memory

// portability
#include <portinfo>

// support
#include <isce/image.h>

// entry point
int main() {
    // units
    auto k = 1024;
    // declare the type of a pixel
    typedef double pixel_t;
    // specify the shape of the data
    isce::image::shape_t shape {1*k, 3*k, 3};
    // make a tile
    isce::image::tile_t tile {shape, isce::image::layout::pixel};

    // compute the size of the payload
    size_t size = sizeof(pixel_t) * tile.size();

    // turn on the info channel
    // pyre::journal::debug_t("isce.image.direct").activate();
    // map a buffer over the file
    void * buffer = isce::image::direct_t::map("image.dat", size, 0, true);
    // and undo it
    isce::image::direct_t::unmap(buffer, size);

    // all done
    return 0;
}

// end of file
