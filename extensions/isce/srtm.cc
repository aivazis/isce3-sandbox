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
#include <isce/srtm.h>
// my declarations
#include "srtm.h"

// the capsule marker
const char * const
isce::extension::srtm::
availabilityMap_capsule = "srtmAvailabilityMap_capsule";

// availability map destructor
static void freeAvailabilityMap(PyObject *);

// availability map constructor
const char * const
isce::extension::srtm::
availabilityMap__name__ = "srtmAvailabilityMap";

const char * const
isce::extension::srtm::
availabilityMap__doc__ = "build a map of the status of SRTM data tiles";

PyObject *
isce::extension::srtm::
availabilityMap(PyObject *, PyObject * args)
{
    // storage for the name of the file
    const char * uri;

    // parse the arguments
    int ok = PyArg_ParseTuple(args, "s:srtmAvailabilityMap", &uri);
    // if something went wrong
    if (!ok) {
        // complain
        return 0;
    }

    // grab the map
    isce::srtm::map_t * map = new isce::srtm::map_t(uri);

    // dress it up and return it
    return PyCapsule_New(map, availabilityMap_capsule, freeAvailabilityMap);
}


// read access
const char * const
isce::extension::srtm::
availabilityMapGet__name__ = "srtmAvailabilityMapGet";

const char * const
isce::extension::srtm::
availabilityMapGet__doc__ = "build a map of the status of SRTM data tiles";

PyObject *
isce::extension::srtm::
availabilityMapGet(PyObject *, PyObject * args)
{
    // storage
    int lat, lon;
    PyObject * capsule;
    // parse the arguments
    int ok = PyArg_ParseTuple(args,
                                  "O!(ii):srtmAvailabilityMapGet",
                                  &PyCapsule_Type, &capsule,
                                  &lat, &lon);
    // if something went wrong
    if (!ok) {
        // complain
        return 0;
    }
    // if the capsule is not valid
    if (!PyCapsule_IsValid(capsule, availabilityMap_capsule)) {
        // set the error string
        PyErr_SetString(PyExc_TypeError, "invalid matrix capsule");
        // and complain
        return 0;
    }
    // check the latitude
    if (lat > 90 || lat < -90) {
        // set the error string
        PyErr_SetString(PyExc_ValueError, "latitude must be in the range (-90, 90)");
        // and complain
        return 0;
    }
    // check the longitude
    if (lon > 180 || lon < -180) {
        // set the error string
        PyErr_SetString(PyExc_ValueError, "longitude must be in the range (-180, 180)");
        // and complain
        return 0;
    }

    // grab the map
    auto & map =
        * static_cast<isce::srtm::map_t *>(PyCapsule_GetPointer(capsule, availabilityMap_capsule));

    // make an index
    isce::srtm::map_t::index_type
        index { static_cast<size_t>(180+lon), static_cast<size_t>(90-lat)};

    // get the value
    auto value = map[index];

    // make a channel
    pyre::journal::debug_t channel("isce.srtm");
    // show me what's about to happend
    channel
        << pyre::journal::at(__HERE__)
        << "tile@(" << lat << "," << lon << ") <- "
        << "(" << index[0] << ", " << index[1] << ") -> "
        << value
        << pyre::journal::endl;

    // dress it up and return it
    return PyLong_FromLong(value);
}


// write access
const char * const
isce::extension::srtm::
availabilityMapSet__name__ = "srtmAvailabilityMapSet";

const char * const
isce::extension::srtm::
availabilityMapSet__doc__ = "build a map of the status of SRTM data tiles";

PyObject *
isce::extension::srtm::
availabilityMapSet(PyObject *, PyObject * args)
{
    // storage
    char value;
    int lat, lon;
    PyObject * capsule;
    // parse the arguments
    int ok = PyArg_ParseTuple(args,
                                  "O!(ii)b:srtmAvailabilityMapSet",
                                  &PyCapsule_Type, &capsule,
                                  &lat, &lon,
                                  &value);
    // if something went wrong
    if (!ok) {
        // complain
        return 0;
    }
    // if the capsule is not valid
    if (!PyCapsule_IsValid(capsule, availabilityMap_capsule)) {
        // set the error string
        PyErr_SetString(PyExc_TypeError, "invalid matrix capsule");
        // and complain
        return 0;
    }
    // check the latitude
    if (lat > 90 || lat < -90) {
        // set the error string
        PyErr_SetString(PyExc_ValueError, "latitude must be in the range (-90, 90)");
        // and complain
        return 0;
    }
    // check the longitude
    if (lon > 180 || lon < -180) {
        // set the error string
        PyErr_SetString(PyExc_ValueError, "longitude must be in the range (-180, 180)");
        // and complain
        return 0;
    }

    // grab the map
    auto & map =
        * static_cast<isce::srtm::map_t *>(PyCapsule_GetPointer(capsule, availabilityMap_capsule));

    // make an index
    isce::srtm::map_t::index_type
        index { static_cast<size_t>(180+lon), static_cast<size_t>(90-lat)};

    // make a channel
    pyre::journal::debug_t channel("isce.srtm");
    // show me what's about to happend
    channel
        << pyre::journal::at(__HERE__)
        << "tile@(" << lat << "," << lon << ") <- "
        << "(" << index[0] << ", " << index[1] << ") <-"
        << (size_t) value
        << pyre::journal::endl;

    // perform the assignment
    map[index] = value;

    // all done
    Py_INCREF(Py_None);
    return Py_None;
}


// helpers
void
freeAvailabilityMap(PyObject * capsule)
{
    // get the capsule signature
    const char * capsule_sig = isce::extension::srtm::availabilityMap_capsule;
    // bail out if the capsule is not valid
    if (!PyCapsule_IsValid(capsule, capsule_sig)) return;
    // grab the map
    isce::srtm::map_t * map =
        static_cast<isce::srtm::map_t *>(PyCapsule_GetPointer(capsule, capsule_sig));
    // deallocate
    delete map;
    // and return
    return;
}


// end of file
