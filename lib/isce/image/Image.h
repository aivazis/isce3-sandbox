// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2017 all rights reserved
//

// code guard
#if !defined(isce_image_Image_h)
#define isce_image_Image_h


// declaration
template <typename pixelT, typename shapeT, typename storageT>
class isce::image::Image : public grid_t<pixelT, shapeT, storageT> {
    // types
public:
    // publish my template parameters
    typedef pixelT pixel_type;
    typedef shapeT shape_type;
    typedef storageT storage_type;
    // dependent types
    typedef typename shape_type::index_type index_type;
    typedef typename shape_type::order_type order_type;
    // my parts
    typedef grid_t<pixel_type, shape_type, storage_type> grid_type;

    // meta-methods
public:
    inline Image(shape_type shape, const storage_type & storage);
    inline Image(shape_type shape, storage_type && storage);
};


#endif

// end of file
