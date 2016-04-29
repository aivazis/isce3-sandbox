// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

// configuration
#include <portinfo>

// externals
#include <Python.h>
#include <isce/version.h>

// my declarations
#include "metadata.h"

// copyright
const char * const
isce::extension::
copyright__name__ = "copyright";

const char * const
isce::extension::
copyright__doc__ = "the project copyright string";

PyObject *
isce::extension::
copyright(PyObject *, PyObject *)
{
    // get the copyright note
    const char * const copyright_note = "isce: (c) 2013-2016 california institute of technology";
    // convert it into a python string and return it
    return Py_BuildValue("s", copyright_note);
}


// version
const char * const
isce::extension::
version__name__ = "version";

const char * const
isce::extension::
version__doc__ = "the project version string";

PyObject *
isce::extension::
version(PyObject *, PyObject *)
{
        return Py_BuildValue("s", isce::version);
}


// end of file
