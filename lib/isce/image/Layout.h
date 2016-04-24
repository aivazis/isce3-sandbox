// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Layout_h)
#define isce_image_Layout_h

// forward declarations
namespace isce {
    namespace image {
        // declarations
        class Layout;
    }
}


// declaration
class isce::image::Layout {
    // meta-methods
public:
    inline Layout(size_t dim0, size_t dim1, size_t dim2);

    // interface
public:
    // container support
    inline const size_t * begin() const;
    inline const size_t * end() const;

    // implementation details
private:
    const size_t _layout[3];
    const size_t _dim = sizeof(_layout)/sizeof(size_t);
};


// get the inline definitions
#define isce_image_Layout_icc
#include "Layout.icc"
#undef isce_image_Layout_icc

#endif

// end of file
