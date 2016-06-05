// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_srtm_h)
#define isce_srtm_h

// externals
#include <stdexcept>
#include <string>
// support
#include <pyre/journal.h>

// forward declarations
namespace isce {
    namespace srtm {
        // local type aliases
        // for filenames
        typedef std::string uri_t;
        // for describing shapes and regions
        typedef off_t offset_t;
        typedef std::size_t size_t;

        // forward declarations of the srtm api classes
        class AvailabilityMap;
    }
}

// support
#include "grid.h"
// the object model
#include "srtm/AvailabilityMap.h"

// namespace additions
namespace isce {
    namespace srtm {
        // tile availability map
        typedef AvailabilityMap map_t;
    }
}


// the implementations of the inlines
// index
#define isce_srtm_AvailabilityMap_icc
#include "srtm/AvailabilityMap.icc"
#undef isce_srtm_AvailabilityMap_icc


#endif

// end of file
