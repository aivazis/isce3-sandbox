// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Index_h)
#define isce_image_Index_h

// declaration
class isce::image::Index {
    // types
public:
    typedef size_t rep_t[_dim]; // the representation of the index values

    // meta-methods
public:
    // construction using explicit values for the indices
    inline Index(size_t line, size_t sample, size_t band);
    // construction from a correctly dimensioned array
    inline explicit Index(rep_t rep);

    // interface
public:
    // size
    inline size_t size() const;

    // equality
    inline bool operator==(const Index & other) const;
    inline bool operator!=(const Index & other) const;

    // indexed access to the components
    inline size_t & operator[](size_t item);
    inline size_t operator[](size_t item) const;

    // support for ranged for loops
    inline const size_t * begin() const;
    inline const size_t * end() const;

    // implementation details
private:
    rep_t _index;
};


// get the inline definitions
#define isce_image_Index_icc
#include "Index.icc"
#undef isce_image_Index_icc

#endif

// end of file
