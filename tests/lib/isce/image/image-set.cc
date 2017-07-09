// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2017 all rights reserved
//

// given a file named "image.dat" in the current directory, map it into memory as an image of
// the specified shape and layout

// portability
#include <portinfo>
// externals
#include <numeric>
// support
#include <isce/image.h>

// entry point
int main() {
    // units
    auto k = 1024;
    // the image data type
    typedef double pixel_t;
    // index realization
    typedef std::array<int, 3> rep_t;
    // pull the shape parts
    typedef isce::image::index_t<rep_t> index_t;
    typedef isce::image::layout_t<index_t> layout_t;
    // my image type
    typedef isce::image::directimage_t<pixel_t, layout_t> image_t;

    // the name of the file
    image_t::uri_type name {"image.dat"};
    // shape
    image_t::shape_type shape {1*k, 3*k, 3};
    // packing order
    image_t::packing_type packing {2u, 1u, 0u};
    // image layout
    image_t::layout_type layout {shape, packing};
    // make an image
    image_t image {name, layout};

    // make channel
    pyre::journal::debug_t channel("isce.image");
    // loop over the image
    for (auto idx : image.layout()) {
        // reduce the index
        auto v = std::accumulate(idx.begin(), idx.end(), 1, std::multiplies<pixel_t>());
        // and store the value
        image[idx] = v;
        // if the channel is active
        if (channel) {
            // show me
            channel
                << pyre::journal::at(__HERE__)
                << "image[" << idx << "] = " << image[idx]
                << pyre::journal::newline;
        }
    }
    // flush
    channel << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
