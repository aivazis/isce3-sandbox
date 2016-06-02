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

// forward declarations
namespace isce {
    namespace image {
        // local type aliases
        // for filenames
        typedef std::string uri_t;
        // for describing shapes and regions
        typedef off_t offset_t;
        typedef std::size_t size_t;

        // forward declarations of the image api classes
        class Direct;
        template <typename> class Image;
        class Index;
        class Iterator;
        class Layout;
        class MemoryMap;
        class Slice;
        class Tile;
        template <typename> class View;

        // constants
        const size_t _dim = 3;
    }
}

// the object model
#include "image/Index.h"
#include "image/Layout.h"
#include "image/Iterator.h"
#include "image/Slice.h"
#include "image/Tile.h"
#include "image/MemoryMap.h"
#include "image/Direct.h"
#include "image/Image.h"
#include "image/View.h"

// namespace additions
namespace isce {
    namespace image {

        // tile shape, layout and indexing
        typedef Index index_t;
        typedef Index shape_t;
        typedef Layout layout_t;
        typedef Iterator iterator_t;
        // tiles
        typedef Tile tile_t;
        // buffer types
        typedef Direct direct_t; // memory mapped file
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
// index
#define isce_image_Index_icc
#include "image/Index.icc"
#undef isce_image_Index_icc

// layout
#define isce_image_Layout_icc
#include "image/Layout.icc"
#undef isce_image_Layout_icc

// iterator
#define isce_image_Iterator_icc
#include "image/Iterator.icc"
#undef isce_image_Iterator_icc

// slice
#define isce_image_Slice_icc
#include "image/Slice.icc"
#undef isce_image_Slice_icc

// tile
#define isce_image_Tile_icc
#include "image/Tile.icc"
#undef isce_image_Tile_icc

// direct
#define isce_image_Direct_icc
#include "image/Direct.icc"
#undef isce_image_Direct_icc

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
