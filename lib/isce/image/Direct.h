// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Direct_h)
#define isce_image_Direct_h


// declaration
class isce::image::Direct {
    // types
public:
    typedef std::string string_t;

    // constants
public:
    static const size_t entireFile = 0;

    // class methods
public:
    static void create(string_t name, size_t size);
    static void * map(string_t name, size_t & size, offset_t offset);
    static void unmap(void * buffer, size_t size);

    // meta-methods
public:
    inline Direct(string_t name, size_t size=entireFile, offset_t offset=0);
    inline ~Direct();

    // interface
public:
    // accessors
    inline size_t size() const;
    inline void * buffer() const;

    // implementation details: data
private:
    size_t _size;
    void * _buffer;

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
