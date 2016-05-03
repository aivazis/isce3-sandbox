// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// portability
#include <portinfo>

// support
#include <isce/image.h>

// entry point
int main() {
    // units
    size_t k = 1024;
    // declare the type of a pixel
    typedef double pixel_t;
    // the name of the file
    isce::image::uri_t name {"image.dat"};
    // specify the shape of the data
    isce::image::shape_t shape {1*k, 3*k, 3};
    // make a tile
    isce::image::tile_t tile {shape, isce::image::layout::pixel};

    // turn on the info channel
    // pyre::journal::debug_t("isce.image.direct").activate();
    // create a file that can fit the payload
    isce::image::constdirect_t::create(name, sizeof(pixel_t)*tile.pixels());

    // all done
    return 0;
}

// end of file
