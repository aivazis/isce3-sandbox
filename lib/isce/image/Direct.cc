// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// portability
#include <portinfo>
// externals
#include <fstream>
// support
#include "../image.h"
// low level stuff
#include <cstring> // for strerror
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <sys/stat.h> // for the mode flags
#include <sys/mman.h> // for mmap

// class methods
// make a file of a specified size
void
isce::image::Direct::
create(string_t name, size_t size) {
    // create a file stream
    std::ofstream image(name, std::ofstream::binary);
    // go to the end of the file
    image.seekp(size - 1);
    // make a byte
    char null = 0;
    // write a byte
    image.write(&null, sizeof(null));

    // make a channel
    pyre::journal::debug_t channel("isce.image.direct");
    // show me
    channel
        << pyre::journal::at(__HERE__)
        << "created '" << name << "' (" << size << " bytes)"
        << pyre::journal::endl;

    // close
    image.close();
    // all done
    return;
}

// memory map the given file
void *
isce::image::Direct::
map(string_t name, size_t size) {
    // open the file using low level IO, since we need its file descriptor
    int fd = ::open(name.c_str(), O_RDWR);
    // map it
    void * buffer = ::mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // check it
    if (buffer == MAP_FAILED) {
        // create a channel
        pyre::journal::error_t channel("isce.image.direct");
        // complain
        channel
            // where
            << pyre::journal::at(__HERE__)
            // what happened
            << "failed to map '" << name << "' onto memory (" << size << " bytes)"
            << pyre::journal::newline
            // why it happened
            << "  reason " << errno << ": " << std::strerror(errno)
            // flush
            << pyre::journal::endl;
        // raise an exception
        throw std::bad_alloc();
    }

    // make a channel
    pyre::journal::debug_t channel("isce.image.direct");
    // show me
    channel
        << pyre::journal::at(__HERE__)
        << "mapped '" << name << "' into memory at " << buffer
        << pyre::journal::endl;

    // close the file
    close(fd);
    // return the payload
    return buffer;
}

// unmap the given buffer
void
isce::image::Direct::
unmap(void * buffer, size_t size) {
    // unmap
    ::munmap(buffer, size);

    // make a channel
    pyre::journal::debug_t channel("isce.image.direct");
    // show me
    channel
        << pyre::journal::at(__HERE__)
        << "unmapped " << size << " bytes from " << buffer
        << pyre::journal::endl;

    // all done
    return;
}

// end of file
