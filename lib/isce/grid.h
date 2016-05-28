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


// end of file
