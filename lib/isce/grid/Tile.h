// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_grid_Tile_h)
#define isce_grid_Tile_h

// declaration
template <std::size_t dim, typename valueT = std::size_t>
class isce::grid::Tile {
    // types
public:
    // for sizing things
    typedef std::size_t size_t;
    // the base type of my values
    typedef std::size_t value_t;
    // my parts
    typedef Layout<dim> layout_t;
    typedef Index<dim, value_t> index_t;
    typedef Index<dim, value_t> shape_t;
    // an alias for me
    typedef Tile<dim, value_t> tile_t;

    // meta-methods
public:
    inline Tile(shape_t shape, layout_t layout);

    // interface
public:
    inline shape_t shape() const;
    inline layout_t layout() const;

    // iteration support
    // iterating in packing order
    iterator_t begin() const;
    iterator_t end() const;

    // implementation details
private:
    const shape_t _shape;
    const layout_t _layout;

};


// get the inline definitions
#define isce_grid_Tile_icc
#include "Tile.icc"
#undef isce_grid_Tile_icc

#endif

// end of file
