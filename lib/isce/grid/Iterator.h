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
    typedef indexT index_type;
    typedef layoutT layout_type;

    // meta-methods
public:
    Iterator(const index_type & begin, const index_type & end, const layout_type & layout);

    // interface
public:
    inline Iterator & operator++();
    inline const index_type & operator*() const;

    // access to my limits
    const index_type & begin() const;
    const index_type & end() const;

    // implementation details
private:
    index_type _current;
    const index_type _begin;
    const index_type _end;
    const layout_type _layout;
};


#endif

// end of file
