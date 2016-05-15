// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Tile_h)
#define isce_image_Tile_h

// slices
#include "Slice.h"


// declaration
class isce::image::Tile {
    // types
public:
    typedef Index index_t;
    typedef Index shape_t;
    typedef Layout layout_t;
    typedef Slice slice_t;
    typedef Tile tile_t;
    typedef Iterator iterator_t;

    // constants
public:
    // constants that specify the interpretation of the index space
    static const size_t line = 0;
    static const size_t sample = 1;
    static const size_t band = 2;

    // meta-methods
public:
    inline Tile(shape_t shape, layout_t layout);

    // interface
public:
    // accessors
    inline shape_t shape() const;
    inline layout_t layout() const;

    // derivative accessors
    inline size_t lines() const;
    inline size_t samples() const;
    inline size_t bands() const;

    // image sizing
    inline size_t pixels() const;

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

    // iterating over slices in arbitrary order; these methods are useful in ranged-for loops
    slice_t slice(const layout_t & order) const;
    slice_t slice(const index_t & begin, const index_t & end) const;
    slice_t slice(const index_t & begin, const index_t & end, const layout_t & layout) const;

    // implementation details
private:
    const shape_t _shape;
    const layout_t _layout;
};


// get the inline definitions
#define isce_image_Tile_icc
#include "Tile.icc"
#undef isce_image_Tile_icc

#define isce_image_Slice_icc
#include "Slice.icc"
#undef isce_image_Slice_icc

#endif

// end of file
