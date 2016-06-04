// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// given a file named "image.dat" in the current directory
//   map it into memory as an image of the specified shape and layout
//   establish a view of it in its natural order

// portability
#include <portinfo>
// support
#include <isce/image.h>

// entry point
int main() {
    // units
    auto k = 1024;
    // the name of the file
    isce::image::uri_t name {"image.dat"};

    // the image data type
    typedef double pixel_t;
    // specify the image dimensions
    isce::image::shape_t shape {1*k, 3*k, 3}; // lines x samples x bands
    // assemble the image layout specification
    isce::image::tile_t tile {shape, isce::image::layout::band};

    // the file may contain headers and other meta-data; the payload starts at
    isce::image::offset_t skip {0};

    // assemble an image
    isce::image::image_t<pixel_t> image {name, tile, skip};
    // make a view
    isce::image::view_t<pixel_t> view(image, tile);

    // make an index
    isce::image::tile_t::index_type index {1*k-1, 3*k-1, 2};
    // make channel
    pyre::journal::debug_t channel("isce.image");
    // show me
    channel
        << pyre::journal::at(__HERE__)
        << "view[ (" << index[0] << ", " << index[1] << ", " << index[2] << ") ] = "
        << view[index]
        << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
