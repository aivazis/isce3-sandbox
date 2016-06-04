// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_h)
#define isce_image_h

// externals
#include <stdexcept>
#include <string>
// support
#include <pyre/journal.h>
#include "grid.h"

// forward declarations
namespace isce {
    namespace image {
        // local type aliases
        // for filenames
        typedef std::string uri_t;
        // for describing shapes and regions
        typedef off_t offset_t;
        typedef std::size_t size_t;

        // buffer types
        typedef isce::grid::direct_t direct_t;

        // template instantiations for local use
        typedef std::array<int, 3> rep_t;
        typedef isce::grid::index_t<rep_t> index_t;
        typedef index_t shape_t;
        typedef isce::grid::layout_t<rep_t> layout_t;
        typedef isce::grid::tile_t<index_t, layout_t> tile_t;
        typedef isce::grid::slice_t<tile_t> slice_t;
        typedef isce::grid::iterator_t<index_t, layout_t> iterator_t;

        // forward declarations of the image api classes
        template <typename> class Image;
        template <typename> class View;
    }
}

// the object model
#include "image/Image.h"
#include "image/View.h"

// namespace additions
namespace isce {
    namespace image {

        // image types
        template <typename pixel> using image_t = Image<pixel>;
        // view types
        template <typename pixel> using view_t = View<pixel>;

        // interleaving
        namespace layout {
            // named index orderings
            const layout_t band  {1, 0, 2};
            const layout_t line  {1, 2, 0};
            const layout_t pixel {2, 1, 0};

            // the familiar ones
            const layout_t c {2, 1, 0};
            const layout_t fortran {0, 1, 2};
        }
    }
}


// the implementations of the inlines
// image
#define isce_image_Image_icc
#include "image/Image.icc"
#undef isce_image_Image_icc

// view
#define isce_image_View_icc
#include "image/View.icc"
#undef isce_image_View_icc


#endif

// end of file
