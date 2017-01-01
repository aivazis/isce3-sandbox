// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2017 all rights reserved
//

// code guard
#if !defined(isce_image_DirectImage_h)
#define isce_image_DirectImage_h


// declaration
template <typename pixelT, typename shapeT, typename storageT>
class isce::image::DirectImage : public directgrid_t<pixelT, shapeT, storageT> {
    // types
public:
    // publish my template parameters
    typedef pixelT pixel_type;
    typedef shapeT shape_type;
    typedef storageT storage_type;
    // dependent types
    typedef typename storage_type::uri_type uri_type;
    typedef typename shape_type::index_type index_type;
    typedef typename shape_type::order_type order_type;
    // my parts
    typedef pyre::geometry::grid_t<pixel_type, shape_type, storage_type> grid_type;

    // meta-methods
public:
    inline DirectImage(uri_type name, shape_type shape);
};


#endif

// end of file
