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
#include <iomanip>
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
        class ConstDirect;
        class Direct;
        class Index;
        class Iterator;
        class Layout;
        class MemoryMap;
        class Tile;

        // constants
        const size_t _dim = 3;
    }
}

// the object model
#include "image/Index.h"
#include "image/Layout.h"
#include "image/Iterator.h"
#include "image/Tile.h"
#include "image/MemoryMap.h"
#include "image/Direct.h"
#include "image/ConstDirect.h"

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
        typedef Direct direct_t;
        typedef ConstDirect constdirect_t;

        // interleaving
        namespace layout {
            // named index orderings
            const layout_t band  {1, 0, 2};
            const layout_t line  {1, 2, 0};
            const layout_t pixel {2, 1, 0};

            // the familiar ones
            const layout_t c {2, 1, 0};
            const layout_t fortran {0,1,2};
        }
    }
}

#endif

// end of file
