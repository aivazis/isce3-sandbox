// -*- C++ -*-
//
// michael a.g. aïvázis
// parasim
// (c) 2003-2016 all rights reserved
//


// externals
#include <iostream>

// support
#include <isce/image.h>

// entry point
int main() {
    // shape
    isce::image::shape_t shape(4,8,3);
    // the interleaving
    isce::image::layout_t layout{isce::image::layout::band};
    // make a tile
    isce::image::tile_t tile(shape, layout);

    // initialize the offset
    size_t offset = 0;
    // loop in packing order
    for (size_t band=0; band < shape.bands(); band++) {
        for (size_t line=0; line < shape.lines(); line++) {
            for (size_t sample=0; sample < shape.samples(); sample++) {
#if 0
                // show me
                std::cout
                    << "at: ("
                    << line << ", " << sample << ", " << band << ")"
                    << std::endl;
#endif
                // make an index
                isce::image::index_t index{line, sample, band};
                // compute the address of the pixel
                size_t pixel = tile.pixel(index);
                // verify the offset has the expected value
                if (offset != pixel) {
                    // open a channel
                    pyre::journal::firewall_t firewall("isce.image.bounds");
                    // complain
                    firewall
                        << pyre::journal::at(__HERE__)
                        << "offset error: " << offset << " != " << pixel
                        << pyre::journal::endl;
                    // and bail
                    return 1;
                }
                // update the counter
                offset++;
            }
        }
    }

    // all done
    return 0;
}


// end of file
