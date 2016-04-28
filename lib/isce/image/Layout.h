// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Layout_h)
#define isce_image_Layout_h


// declaration
class isce::image::Layout {
    // meta-methods
public:
    inline Layout(size_t dim0, size_t dim1, size_t dim2);

    // interface
public:
    // indexed access
    inline size_t operator[](size_t item) const;

    // container support
    inline const size_t * begin() const;
    inline const size_t * end() const;

    // implementation details
private:
    const size_t _layout[_dim];
};


// get the inline definitions
#define isce_image_Layout_icc
#include "Layout.icc"
#undef isce_image_Layout_icc

#endif

// end of file
