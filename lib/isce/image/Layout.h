// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Layout_h)
#define isce_image_Layout_h


// declaration
class isce::image::Layout {
    // types
public:
    typedef size_t rep_t[_dim]; // the representation of the index values

    // meta-methods
public:
    inline Layout(size_t dim0, size_t dim1, size_t dim2);

    // interface
public:
    // indexed access
    inline size_t operator[](size_t item) const;

    // support for ranged for loops
    inline const size_t * begin() const;
    inline const size_t * end() const;

    // implementation details
private:
    const rep_t _layout;
};


#endif

// end of file
