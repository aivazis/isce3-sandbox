// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2017 all rights reserved
//

// code guard
#if !defined(isce_image_public_h)
#define isce_image_public_h

// externals
#include <stdexcept>
#include <string>
// support
#include <pyre/journal.h>
#include <pyre/memory.h>
#include <pyre/geometry.h>

// pull useful typedefs
namespace isce {
    namespace image {
        // file names
        typedef pyre::memory::uri_t uri_t;
        // grid layout parts
        template <typename repT> using index_t = pyre::geometry::index_t<repT>;
        template <typename repT> using order_t = pyre::geometry::order_t<repT>;
        template <typename indexT, typename orderT>
        using shape_t = pyre::geometry::tile_t<indexT, orderT>;

        // grid
        template <typename cellT, typename tileT, typename storageT>
        using grid_t = pyre::geometry::grid_t<cellT, tileT, storageT>;
        // direct grid
        template <typename cellT, typename tileT, typename directT = pyre::memory::direct_t>
        using directgrid_t = pyre::geometry::directgrid_t<cellT, tileT, directT>;
    }
}

// forward declarations
namespace isce {
    namespace image {
        // forward declarations of the image api classes
        template <typename pixelT, typename shapeT, typename storageT> class Image;
        template <typename pixelT, typename shapeT, typename storageT> class DirectImage;
    }
}

// type aliases for the above; these are the recommended type names for public access
namespace isce {
    namespace image {
        // image_t: you specify pixel, shape, and storage
        template <typename pixelT, typename shapeT, typename storageT>
        using image_t = Image<pixelT, shapeT, storageT>;

        // directimage_t: specify pixel, shape; storage is memory mapped;
        // instantiate with {constdirect_t> for read-only access
        template <typename pixelT, typename shapeT, typename storageT = pyre::memory::direct_t>
        using directimage_t = DirectImage<pixelT, shapeT, storageT>;
    }
}

// the object model
#include "Image.h"
#include "DirectImage.h"

// the implementations of the inlines
// image
#define isce_image_Image_icc
#include "Image.icc"
#undef isce_image_Image_icc

// memory mapped image
#define isce_image_DirectImage_icc
#include "DirectImage.icc"
#undef isce_image_DirectImage_icc

#endif

// end of file
