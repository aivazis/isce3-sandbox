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
    // names of files
    typedef isce::image::uri_t uri_t;
    // index realization
    typedef std::array<int, 3> rep_t;
    // pull the shape parts
    typedef isce::image::index_t<rep_t> index_t;
    typedef isce::image::order_t<rep_t> order_t;
    typedef isce::image::shape_t<index_t, order_t> shape_t;
    // my image type
    typedef isce::image::directimage_t<pixel_t, shape_t> image_t;

    // the name of the file
    uri_t name {"image.dat"};
    // extent
    index_t extent {1*k, 3*k, 3};
    // layout
    order_t layout {2, 1, 0};
    // image shape
    shape_t shape {extent, layout};
    // make an image
    image_t image {name, shape};

    // make channel
    pyre::journal::debug_t channel("isce.image");
    // loop over the image
    for (auto idx : image.shape()) {
        // reduce the index
        auto v = std::accumulate(idx.begin(), idx.end(), 1, std::multiplies<pixel_t>());
        // verify we read the correct value
        if (image[idx] != v) {
            // make a channel
            pyre::journal::firewall_t firewall("pyre.geometry");
            // show me
            firewall
                << pyre::journal::at(__HERE__)
                << "image[" << idx << "] = " << image[idx] << " != " << v
                << pyre::journal::endl;
            // and bail
            return 1;
        }
    }
    // flush
    channel << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
