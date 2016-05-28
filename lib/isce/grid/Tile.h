// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_grid_Tile_h)
#define isce_grid_Tile_h

// declaration
template <typename indexT, typename layoutT>
class isce::grid::Tile {
    // types
public:
    typedef indexT index_type;
    typedef layoutT layout_type;

    // meta-methods
public:

    // interface
public:

    // implementation details
private:
    const index_type _shape;
    const layout_type _layout;
};


#endif

// end of file
