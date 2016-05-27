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

// namespace additions
namespace isce {
    namespace grid {
        // type aliases
        template <typename repT> using index_t = Index<repT>;
        template <typename repT> using layout_t = Layout<repT>;

        template <typename indexT, typename layoutT = layout_t<typename indexT::rep_type>>
        using iterator_t = Iterator<indexT, layoutT>;
    }
}

#endif

// end of file
