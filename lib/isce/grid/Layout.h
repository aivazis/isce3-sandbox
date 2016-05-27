// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// code guard
#if !defined(isce_grid_Layout_h)
#define isce_grid_Layout_h


// declaration
template <typename repT>
class isce::grid::Layout {
    // types
public:
    // the container with the index order
    typedef repT rep_type;
    // for sizing things
    typedef typename rep_type::size_type size_type;
    // the base type of my values
    typedef typename rep_type::value_type value_type;

    // meta-methods
public:
    // the constructor is a variadic template; it enables construction of the rep using
    // initializer lists
    template <typename... argT> inline Layout(argT... arg);

    // interface
public:
    // size
    inline constexpr auto size() const;

    // indexed access
    inline auto operator[](size_type item) const;

    // support for ranged for loops
    inline auto begin() const;
    inline auto end() const;

    // implementation details
private:
    const rep_type _layout;
};


// get the inline definitions
#define isce_grid_Layout_icc
#include "Layout.icc"
#undef isce_grid_Layout_icc

#endif

// end of file
