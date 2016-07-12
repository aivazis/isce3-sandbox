// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_srtm_Tile_h)
#define isce_srtm_Tile_h


// declaration
class isce::srtm::Tile {
    // types
public:
    // the payload type
    typedef int16_t data_type;

    // my shape specification
    // storage for my indices
    typedef std::array<int, 2> rep_type;
    // my tile parts
    typedef isce::grid::index_t<rep_type> index_type;
    typedef isce::grid::layout_t<rep_type> layout_type;
    typedef isce::grid::tile_t<index_type, layout_type> tile_type;

    // meta-methods
public:
    inline Tile(const void * rawdata, int arcsecondsPerPixel=1);

    // interface
    inline const tile_type & tile() const;
    inline data_type get(index_type index) const;

    // syntactic sugar
    inline data_type operator[](index_type index) const;

    // implementation details
private:
    // data members
    tile_type _tile;
    const data_type * const _data; // tiles are views on foreign data; they don't own any memory

    // disable copy semantics
private:
    Tile(const Tile &) = delete;
    Tile & operator=(const Tile &) = delete;
};


#endif

// end of file
