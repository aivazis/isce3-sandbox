// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//


// externals
#include <iostream>

// support
#include <isce/image.h>

// entry point
int main() {
    // shape
    isce::image::shape_t shape{4,8,3};
    // the interleaving
    isce::image::layout_t layout{isce::image::layout::line};
    // the index
    isce::image::index_t index{2,3,2};
    // make a tile
    isce::image::tile_t tile(shape, layout);

#if 0
    std::cout
        << "shape  : ("
        << shape(0) << ", " << shape(1) << ", " << shape(2)
        << ")" << std::endl
        << "layout: ("
        << layout(0) << ", " << layout(1) << ", " << layout(2)
        << ")" << std::endl
        << "index  : ("
        << index(0) << ", " << index(1) << ", " << index(2)
        << ")" << std::endl
        << "offset: " << tile.pixel(index) << std::endl;
#endif

    // all done
    return 0;
}


// end of file
