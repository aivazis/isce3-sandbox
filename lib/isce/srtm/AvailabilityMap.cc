// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// portability
#include <portinfo>
// externals
#include <cstdint>    // for sized types
#include <fcntl.h>    // for open
#include <unistd.h>   // for close
#include <sys/stat.h> // for the mode flags
// support
#include "../srtm.h"

// helpers
isce::srtm::AvailabilityMap::direct_type
isce::srtm::AvailabilityMap::
map(uri_type uri, const tile_type & tile) {
    // compute the size of the availability map
    size_type size = sizeof(char) * tile.size();

    // check whether the file exists
    int fd = ::open(uri.c_str(), O_RDONLY);
    // if it doesn't
    if (fd < 0) {
        // make it
        direct_type::create(uri, size);
    // if it does
    } else {
        // close it; we will re-open with the correct permissions when we memory map it
        ::close(fd);
    }

    // if we get this far, we got our map
    return direct_type {uri, size, 0, true};
}


// end of file
