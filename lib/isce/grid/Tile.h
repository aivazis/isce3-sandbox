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
    // for sizing things
    typedef std::size_t size_type;
    // aliases for my parts
    typedef indexT index_type;
    typedef layoutT layout_type;
    // iterator
    typedef Iterator<index_type, layout_type> iterator_type;

    // meta-methods
public:
    Tile(index_type shape, layout_type layout);

    // interface
public:
    // accessors
    inline const auto & shape() const;
    inline const auto & layout() const;

    // the number of cells in this tile
    inline auto size() const;

    // compute the pixel offset implied by a given index
    // compute the index that corresponds to a given offset
    inline auto offset(const index_type & index) const;
    inline auto index(size_type offset) const;

    // syntactic sugar for the pair above
    inline auto operator[](const index_type & index) const;
    inline auto operator[](size_type offset) const;

    // iteration support
    inline auto begin() const;
    inline auto end() const;

    // implementation details
private:
    const index_type _shape;
    const layout_type _layout;
};


#endif

// end of file
