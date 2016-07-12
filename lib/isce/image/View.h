// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_View_h)
#define isce_image_View_h


// declaration
template <typename pixelT>
class isce::image::View {
    // types
public:
    // publish my template parameters
    typedef pixelT pixel_type;
    // local aliases for specifying my parts
    typedef tile_t tile_type;
    typedef tile_type::index_type index_type;
    typedef Image<pixel_type> image_type;

    // meta-methods
public:
    inline View(
                const image_type & image,   // the underlying image
                tile_type tile);            // the view shape and memory layout

    // interface
    inline pixel_type get(index_type index) const;

    // syntactic sugar
    inline pixel_type operator[](index_type index) const;

    // implementation details
private:
    // data members
    const tile_type _tile;
    const image_type & _image;
};


#endif

// end of file
