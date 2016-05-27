// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// exercise grid layout construction:
//   verify that all the parts are accessible through the public headers
//   verify constructor signatures
//   assemble a layout
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
    typedef isce::grid::layout_t<rep_t> layout_t;
    // make the interleaving
    layout_t layout = {0, 1, 2, 3};

    // make a firewall
    pyre::journal::firewall_t channel("isce.grid");

    // check the values one by one
    for (layout_t::size_type i=0; i < layout.size(); ++i) {
        // check this one
        if (layout[i] != static_cast<layout_t::value_type>(i)) {
            // complain
            channel
                << pyre::journal::at(__HERE__)
                << "index mismatch: " << layout[i] << " != " << i
                << pyre::journal::endl;
            // and bail
            return 1;
        }
    }

    // all done
    return 0;
}

// end of file
