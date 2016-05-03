// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_ConstDirect_h)
#define isce_image_ConstDirect_h


// declaration
class isce::image::ConstDirect : public isce::image::MemoryMap {
    // meta-methods
public:
    inline ConstDirect(string_t name, size_t size=entireFile, offset_t offset=0);
    inline ~ConstDirect();

    // interface
public:
    // accessors
    inline size_t size() const;
    inline const void * buffer() const;

    // implementation details: data
private:
    const void * const _buffer; // the buffer is read only...
    const size_t _size;         // need this during destruction

    // disable automatic life cycle management
private:
    ConstDirect(const ConstDirect &) = delete;
    ConstDirect(const ConstDirect &&) = delete;
    ConstDirect & operator=(const ConstDirect &) = delete;
    ConstDirect & operator=(const ConstDirect &&) = delete;
};


// get the inline definitions
#define isce_image_ConstDirect_icc
#include "ConstDirect.icc"
#undef isce_image_ConstDirect_icc

#endif

// end of file
