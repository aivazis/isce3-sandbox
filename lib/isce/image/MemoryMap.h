// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_MemoryMap_h)
#define isce_image_MemoryMap_h


// declaration
// this class is a wrapper around the os calls
class isce::image::MemoryMap {
    // constants
public:
    static const size_t entireFile = 0;

    // class methods
public:
    static void create(string_t name, size_t size);
    static void * map(string_t name, size_t & size, offset_t offset, bool writable);
    static void unmap(const void * buffer, size_t size);
};

#endif

// end of file
