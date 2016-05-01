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
    isce::image::string_t name {"image.dat"};
    // specify the shape of the data
    isce::image::shape_t shape {1*k, 3*k, 3};
    // make a tile
    isce::image::tile_t tile {shape, isce::image::layout::pixel};

    // compute the size of the payload
    size_t size = sizeof(pixel_t) * tile.pixels();

    // map the file
    // turn on the info channel
    pyre::journal::debug_t("isce.image.direct").activate();
    // map a buffer over the file; it gets unmapped on destruction
    isce::image::direct_t map {name, size};
    // and make a copy
    isce::image::direct_t clone {map};

    // all done
    return 0;
}

// end of file
