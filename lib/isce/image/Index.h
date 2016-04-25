// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Index_h)
#define isce_image_Index_h

// externals
#include <pyre/journal.h>

// forward declarations
namespace isce {
    namespace image {
        // declarations
        class Index;
    }
}


// declaration
class isce::image::Index {
    // meta-methods
public:
    inline Index(size_t line, size_t sample, size_t band);

    // interface
public:
    // indexed access
    inline size_t operator[](size_t item) const;

    // implementation details
private:
    const size_t _index[3];
    const size_t _dim = sizeof(_index)/sizeof(size_t);
};


// get the inline definitions
#define isce_image_Index_icc
#include "Index.icc"
#undef isce_image_Index_icc

#endif

// end of file
