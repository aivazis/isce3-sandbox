// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Image_h)
#define isce_image_Image_h


// declaration
template <typename pixelT>
class isce::image::Image {
    // types
public:
    // publish my template parameters
    typedef pixelT pixel_type;
    // local aliases for specifying my parts
    typedef off_t offset_type;
    typedef direct_t map_type;
    typedef tile_t tile_type;
    typedef tile_type::index_type index_type;

    // meta-methods
public:
    inline Image(
                 uri_t source,           // the name of the file
                 tile_type tile,         // the image shape and memory layout
                 offset_type offset = 0, // the offset to the actual image data
                 bool writable = false); // access policy

    // interface
    inline pixel_type get(index_type index) const;

    // syntactic sugar
    inline pixel_type operator[](index_type index) const;

    // implementation details
private:
    // data members
    map_type _source;
    tile_type _tile;
    // my buffer
    pixel_type * _data;
};


#endif

// end of file
