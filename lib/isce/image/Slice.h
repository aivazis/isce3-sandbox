// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Slice_h)
#define isce_image_Slice_h


// declaration
class isce::image::Slice {
    // types
public:
    typedef class Index index_t;
    typedef class Index shape_t;
    typedef class Layout layout_t;
    typedef class Tile tile_t;
    typedef class Iterator iterator_t;

    // meta-methods
public:
    inline Slice(const tile_t & tile, const layout_t & layout);
    inline Slice(const tile_t & tile,
                 const index_t & begin, const index_t & end, const layout_t & layout);

    // interface
public:
    // accessors
    inline shape_t shape() const;
    inline layout_t layout() const;

    // compute the pixel offset at the given index
    inline size_t offset(index_t index) const;
    // compute the index at a given offset
    inline index_t index(size_t offset) const;

    // syntactic sugar for the above
    inline size_t operator[](index_t index) const;
    inline index_t operator[](size_t offset) const;

    // iteration support
    // iterating in packing order
    iterator_t begin() const;
    iterator_t end() const;

    // implementation details
private:
    // the reference tile
    const tile_t & _tile;
    // my parameters
    const index_t _begin;
    const index_t _end;
    const layout_t _layout;
};


#endif

// end of file
