// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_grid_Slice_h)
#define isce_grid_Slice_h


// declaration
template <typename tileT>
class Slice {
    // types
public:
    typedef tileT tile_type;
    typedef typename tile_type::index_type index_type;
    typedef typename tile_type::layout_type layout_type;
    typedef typename tile_type::iterator_type iterator_type;
};


# endif

// end of file
