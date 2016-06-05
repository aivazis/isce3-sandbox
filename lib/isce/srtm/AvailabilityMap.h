// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_srtm_AvailabilityMap_h)
#define isce_srtm_MemoryMap_h


// declaration
// this class is a wrapper around the os calls
class isce::srtm::AvailabilityMap {
    // types
public:
    typedef isce::grid::direct_t direct_type;
    typedef direct_type::uri_type uri_type;
    typedef direct_type::size_type size_type;

    // for my tile
    typedef std::array<size_t, 2> rep_type;
    typedef isce::grid::index_t<rep_type> index_type;
    typedef isce::grid::layout_t<rep_type> layout_type;
    typedef isce::grid::tile_t<index_type, layout_type> tile_type;

    // meta-methods
public:
    inline AvailabilityMap(uri_type uri);

    // interface
public:
    inline auto & operator[](const index_type &index);
    inline auto operator[](const index_type & index) const;

    // implementation details
    // helpers
private:
    direct_type map(uri_type uri, const tile_type & tile);

    // data
private:
    tile_type _tile;
    direct_type _map;
};

#endif

// end of file
