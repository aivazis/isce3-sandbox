// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_View_h)
#define isce_image_View_h


// declaration
template <typename pixel>
class isce::image::View {
    // types
public:
    // publish my template parameters
    typedef pixel pixel_t;
    // local aliases for specifying my parts
    typedef Tile tile_t;
    typedef tile_t::index_t index_t;
    typedef Image<pixel> image_t;

    // meta-methods
public:
    View(const image_t & image,   // the underlying image
         tile_t tile);            // the view shape and memory layout

    // interface
    inline pixel_t get(tile_t::index_t index) const;

    // syntactic sugar
    inline pixel_t operator[](tile_t::index_t index) const;

    // implementation details
private:
    // data members
    const tile_t _tile;
    const image_t & _image;
};


// get the inline definitions
#define isce_image_View_icc
#include "View.icc"
#undef isce_image_View_icc

#endif

// end of file
