// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Tile_h)
#define isce_image_Tile_h

// support
#include "Index.h"
#include "Layout.h"
#include "Shape.h"

// forward declarations
namespace isce {
    namespace image {
        // declarations
        class Tile;
    }
}


// declaration
class isce::image::Tile {
    // types
public:
    typedef Index index_t;
    typedef Layout layout_t;
    typedef Shape shape_t;

    // meta-methods
public:
    inline Tile(shape_t shape, layout_t layout);

    // interface
public:
    inline size_t operator[](index_t index) const;

    // implementation details
private:
    const shape_t _shape;
    const layout_t _layout;
};


// get the inline definitions
#define isce_image_Tile_icc
#include "Tile.icc"
#undef isce_image_Tile_icc

#endif

// end of file
