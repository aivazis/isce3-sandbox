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

    // class methods
public:
    static void create(string_t name, size_t size);
    static void * map(string_t name, size_t size);
    static void unmap(void * buffer, size_t size);

    // meta-methods
public:
    inline Direct(string_t name, size_t size);
    inline ~Direct();

    // interface
public:

    // implementation details: data
private:
    void * _buffer;
    size_t _size;

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
