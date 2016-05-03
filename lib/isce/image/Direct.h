// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Direct_h)
#define isce_image_Direct_h


// declaration
class isce::image::Direct : public isce::image::MemoryMap {
    // meta-methods
public:
    inline Direct(uri_t name, size_t size=entireFile, offset_t offset=0);
    inline ~Direct();

    // interface
public:
    // accessors
    inline size_t size() const;
    inline void * buffer() const;

    // implementation details: data
private:
    void * const _buffer; // the buffer payload is writable; the pointer itself is not
    const size_t _size;   // need this during destruction

    // disable automatic life cycle management
private:
    Direct(const Direct &) = delete;
    Direct(const Direct &&) = delete;
    Direct & operator=(const Direct &) = delete;
    Direct & operator=(const Direct &&) = delete;
};


// get the inline definitions
#define isce_image_Direct_icc
#include "Direct.icc"
#undef isce_image_Direct_icc

#endif

// end of file
