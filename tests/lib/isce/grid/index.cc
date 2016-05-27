// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// exercise grid index construction:
//   verify that all the parts are accessible through the public headers
//   verify constructor signatures
//   assemble a index
//   verify it can be iterated

// portability
#include <portinfo>
// support
#include <isce/grid.h>

// entry point
int main() {
    // fix the representation
    typedef std::array<int, 4> rep_t;
    // alias
    typedef isce::grid::index_t<rep_t> index_t;
    // make an index
    index_t idx { 0, 1, 2, 3 };

    // make a channel
    pyre::journal::debug_t channel("isce.grid");
    // and display information about the tile index
    channel << pyre::journal::at(__HERE__) << "index : (";
    // go through the values
    for (auto value : idx) {
        // inject them
        channel << " " << value;
    }
    // flush
    channel << " )" << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
