// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Iterator_h)
#define isce_image_Iterator_h


// declaration
class isce::image::Iterator {
    // types
public:
    typedef class Index index_t;
    typedef class Index shape_t;
    typedef class Layout layout_t;

    // meta-methods
public:
    inline Iterator(const shape_t & shape, const layout_t & layout);
    inline Iterator(const index_t & current, const shape_t & shape, const layout_t & layout);

    // interface
public:
    inline bool operator==(const Iterator & other) const;
    inline bool operator!=(const Iterator & other) const;

    inline Iterator& operator++();
    inline const index_t & operator*() const;

    // implementation details
private:
    index_t _current;
    const shape_t _shape;
    const layout_t _layout;
};


// get the inline definitions
#define isce_image_Iterator_icc
#include "Iterator.icc"
#undef isce_image_Iterator_icc

#endif

// end of file
