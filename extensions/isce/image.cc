// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// configuration
#include <portinfo>

// externals
#include <Python.h>
// support
#include <isce/image.h>
// my declarations
#include "image.h"


// image constructor
const char * const
isce::extension::image::
newImage_float__name__ = "newImage_float";

const char * const
isce::extension::image::
newImage_float__doc__ = "create a new image object whose pixels are floats";

PyObject *
isce::extension::image::
newImage_float(PyObject *, PyObject *)
{
    // all done
    Py_INCREF(Py_None);
    return Py_None;
}


// view constructor
const char * const
isce::extension::image::
newView_float__name__ = "newView_float";

const char * const
isce::extension::image::
newView_float__doc__ = "create a new view to an image whose pixels are floats";

PyObject *
isce::extension::image::
newView_float(PyObject *, PyObject *)
{
    // all done
    Py_INCREF(Py_None);
    return Py_None;
}


// end of file
