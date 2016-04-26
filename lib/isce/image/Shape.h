// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Shape_h)
#define isce_image_Shape_h


// declaration
class isce::image::Shape {
    // meta-methods
public:
    inline Shape(size_t lines, size_t samples, size_t bands);

    // interface
public:
    // accessors
    inline size_t lines() const;
    inline size_t samples() const;
    inline size_t bands() const;

    // indexed access
    inline size_t operator[](size_t item) const;

    // implementation details
private:
    const size_t _shape[_dim];
};


// get the inline definitions
#define isce_image_Shape_icc
#include "Shape.icc"
#undef isce_image_Shape_icc

#endif

// end of file
