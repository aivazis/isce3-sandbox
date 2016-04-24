// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_h)
#define isce_image_h

// support
#include "image/Tile.h"

// namespace additions
namespace isce {
    namespace image {

        // type aliases
        typedef Index index_t;
        typedef Layout layout_t;
        typedef Shape shape_t;
        typedef Tile tile_t;

        // interleaving constants
        namespace layout {
            // constants
            const layout_t band{1, 0, 2};
            const layout_t line{1, 2, 0};
            const layout_t pixel{2, 1, 0};
        }
    }
}

#endif

// end of file
