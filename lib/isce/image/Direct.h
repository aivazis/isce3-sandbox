// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_image_Direct_h)
#define isce_image_Direct_h

//
// Direct is the life cycle manager of a memory mapping
//
// It is a low level concept and should be considered an implementation detail; as such, you
// should probably avoid using it directly
//

// declaration
class isce::image::Direct : public isce::image::MemoryMap {
    // meta-methods
public:
    // constructor
    explicit inline
    Direct(uri_t name,               // the name of the file
           size_t size = entireFile, // how much of the file to map
           offset_t offset = 0,      // starting at this offset from the beginning
           bool writable = false);   // type of access to grant
    // destructor
    inline ~Direct();

    // interface
public:
    // accessors
    inline size_t size() const;
    inline void * buffer() const;

    // implementation details: data
private:
    void * const _buffer; // the buffer payload may be writable; the pointer itself is not
    const size_t _size;   // need this during destruction

    // disable automatic life cycle management
private:
    Direct(const Direct &) = delete;
    Direct(const Direct &&) = delete;
    Direct & operator=(const Direct &) = delete;
    Direct & operator=(const Direct &&) = delete;
};


#endif

// end of file
