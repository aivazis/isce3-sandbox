// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// access the low level interface to create a file that can fit an image of a specified size
//
// N.B.: this test leaves behind a file named "image.dat" that is used by the other tests; it
// must be cleaned up after the tests are run

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
    // the name of the file
    isce::image::uri_t name {"image.dat"};
    // specify the shape of the data
    isce::image::shape_t shape {1*k, 3*k, 3};
    // make a tile
    isce::image::tile_t tile {shape, isce::image::layout::pixel};

    // turn on the info channel
    // pyre::journal::debug_t("isce.image.direct").activate();
    // create a file that can fit the payload
    isce::image::direct_t::create(name, sizeof(pixel_t)*tile.size());

    // all done
    return 0;
}

// end of file
