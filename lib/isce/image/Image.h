// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Image_h)
#define isce_image_Image_h


// declaration
template <typename pixel>
class isce::image::Image {
    // types
public:
    // publish my template parameters
    typedef pixel pixel_t;
    // local aliases for specifying my parts
    typedef off_t offset_t;
    typedef Direct map_t;
    typedef Tile tile_t;
    typedef tile_t::index_t index_t;

    // meta-methods
public:
    Image(uri_t source,           // the name of the file
          tile_t tile,            // the image shape and memory layout
          offset_t offset = 0,    // the offset from the beginning of the file to the image data
          bool writable = false); // access policy

    // interface
    inline pixel_t get(tile_t::index_t index) const;

    // syntactic sugar
    inline pixel_t operator[](tile_t::index_t index) const;

    // implementation details
private:
    // data members
    map_t _source;
    tile_t _tile;
    // my buffer
    pixel_t * _data;
};


#endif

// end of file
