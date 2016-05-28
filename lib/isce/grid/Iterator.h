// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_grid_Iterator_h)
#define isce_grid_Iterator_h


// declaration
template <typename indexT, typename layoutT>
class isce::grid::Iterator {
    // types
public:
    // my parts
    typedef indexT index_t;
    typedef layoutT layout_t;

    // meta-methods
public:
    Iterator(const index_t & begin, const index_t & end, const layout_t & layout);

    // interface
public:
    inline Iterator & operator++();
    inline const index_t & operator*() const;

    // access to my limits
    const index_t & begin() const;
    const index_t & end() const;

    // implementation details
private:
    index_t _current;
    const index_t _begin;
    const index_t _end;
    const layout_t _layout;
};


#endif

// end of file
