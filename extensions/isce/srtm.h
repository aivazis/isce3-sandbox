// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

#if !defined(isce_extension_srtm_h)
#define isce_extension_srtm_h


// place everything in my private namespace
namespace isce {
    namespace extension {

        // protect srtm methods
        namespace srtm {
            // the capsule name
            extern const char * const availabilityMap_capsule;

            // srtm availability map: constructor
            extern const char * const availabilityMap__name__;
            extern const char * const availabilityMap__doc__;
            PyObject * availabilityMap(PyObject *, PyObject *);

            // srtm availability map: read acces
            extern const char * const availabilityMapGet__name__;
            extern const char * const availabilityMapGet__doc__;
            PyObject * availabilityMapGet(PyObject *, PyObject *);

            // srtm availability map: write acces
            extern const char * const availabilityMapSet__name__;
            extern const char * const availabilityMapSet__doc__;
            PyObject * availabilityMapSet(PyObject *, PyObject *);

        } // of namespace srtm

    } // of namespace extension`
} // of namespace isce


#endif

// end of file
