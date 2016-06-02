// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// comparison of the offset maps for band, line and pixel interleaved tiles
// with three tiles, one for each interleaving strategy:
//   generate a sequence of indices in pixel order
//   display the corresponding offset values size by side
//
// the test is silenced by default; to display the map, activate its journal channel by setting
// the DEBUG_OPT environment variable. e.g.:
//   DEBUG_OPT=isce.image.tile tile-maps
//


// portability adjustments
#include <portinfo>
// externals
#include <iomanip>
// support
#include <isce/image.h>

// entry point
int main() {
    // shape
    isce::image::shape_t shape = {2,4,3};
    // make a pixel interleaved tile
    isce::image::tile_t pixel = {shape, isce::image::layout::pixel};
    // a line interleaved tile
    isce::image::tile_t line = {shape, isce::image::layout::line};
    // and a band interleaved tile
    isce::image::tile_t band = {shape, isce::image::layout::band};

    // make a channel
    pyre::journal::debug_t channel("isce.image.tile");
    // if the channel is not active
    if (!channel) {
        // we are done
        return 0;
    }

    // otherwise
    channel
        // sign in
        << pyre::journal::at(__HERE__)
        // print the header
        <<  "  index  | pixel | line | band " << pyre::journal::newline
        // and a separator
        << "---------+-------+------+------" << pyre::journal::newline;

    // go through all possible indices in pixel order
    for (auto index : pixel) {
        // show me
        channel
            // the index
            << " (" << index[0] << "," << index[1] << "," << index[2] << ") "
            << "|"
            // the pixel mapping
            << " " << std::setw(5) << pixel[index] << " "
            << "|"
            // the line mapping
            << " " << std::setw(4) << line[index] << " "
            << "|"
            // the band mapping
            << " " << std::setw(4) << band[index] << " "
            // eol
            << pyre::journal::newline;
    }

    // flush
    channel << pyre::journal::endl;

    // all done
    return 0;
}

// end of file
