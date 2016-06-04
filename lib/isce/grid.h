// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_grid_h)
#define isce_grid_h

// externals
#include <stdexcept>
#include <utility>
#include <array>
// support
#include <pyre/journal.h>

// forward declarations
namespace isce {
    namespace grid {
        // local type aliases
        // for filenames
        typedef std::string uri_t;
        // for describing shapes and regions
        typedef off_t offset_t;
        typedef std::size_t size_t;

        // grid packing order
        template <typename repT> class Layout;
        // grid indices
        template <typename repT> class Index;
        // iterators over index ranges
        template <typename indexT, typename layoutT> class Iterator;
        // tiles
        template <typename indexT, typename layoutT> class Tile;
        // slices
        template <typename tileT> class Slice;

        class Direct;
        class MemoryMap;

        // operators on indices
        // equality
        template <typename repT>
        auto operator== (const Index<repT> &, const Index<repT> &);
        // inequality
        template <typename repT>
        auto operator!= (const Index<repT> &, const Index<repT> &);

        // operators on iterators
        // equality
        template <typename indexT, typename layoutT>
        auto operator== (const Iterator<indexT, layoutT> &, const Iterator<indexT, layoutT> &);
        // inequality
        template <typename indexT, typename layoutT>
        auto operator!= (const Iterator<indexT, layoutT> &, const Iterator<indexT, layoutT> &);
    }
}

// the object model
#include "grid/Layout.h"
#include "grid/Index.h"
#include "grid/Iterator.h"
#include "grid/Tile.h"
#include "grid/Slice.h"
#include "grid/MemoryMap.h"
#include "grid/Direct.h"

// namespace additions
namespace isce {
    namespace grid {
        // type aliases
        template <typename repT> using index_t = Index<repT>;
        template <typename repT> using layout_t = Layout<repT>;

        template <typename indexT, typename layoutT = layout_t<typename indexT::rep_type>>
            using iterator_t = Iterator<indexT, layoutT>;

        template <typename indexT, typename layoutT = layout_t<typename indexT::rep_type>>
            using tile_t = Tile<indexT, layoutT>;

        template <typename tileT> using slice_t = Slice<tileT>;

        // buffer types
        typedef Direct direct_t; // memory mapped file
    }
}

#endif

// the implementations
// layout
#define isce_grid_Layout_icc
#include "grid/Layout.icc"
#undef isce_grid_Layout_icc

// index
#define isce_grid_Index_icc
#include "grid/Index.icc"
#undef isce_grid_Index_icc

// iterator
#define isce_grid_Iterator_icc
#include "grid/Iterator.icc"
#undef isce_grid_Iterator_icc

// tile
#define isce_grid_Tile_icc
#include "grid/Tile.icc"
#undef isce_grid_Tile_icc

// slice
#define isce_grid_Slice_icc
#include "grid/Slice.icc"
#undef isce_grid_Slice_icc

// slice
#define isce_grid_Direct_icc
#include "grid/Direct.icc"
#undef isce_grid_Direct_icc


// end of file
