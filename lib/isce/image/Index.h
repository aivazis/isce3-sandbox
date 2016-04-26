// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Index_h)
#define isce_image_Index_h


// declaration
class isce::image::Index {
    // meta-methods
public:
    inline Index(size_t line, size_t sample, size_t band);

    // interface
public:
    // equality
    inline bool operator==(const Index & other) const;
    inline bool operator!=(const Index & other) const;

    // indexed access
    inline size_t & operator[](size_t item);
    inline size_t operator[](size_t item) const;

    // implementation details
private:
    size_t _index[_dim];
};


// get the inline definitions
#define isce_image_Index_icc
#include "Index.icc"
#undef isce_image_Index_icc

#endif

// end of file
