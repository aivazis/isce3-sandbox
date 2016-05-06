// -*- C++ -*-
//
// michael a.g. aïvázis <michael.aivazis@para-sim.com>
// (c) 2003-2016 all rights reserved
//

#if !defined(isce_extension_image_h)
#define isce_extension_image_h


// place everything in my private namespace
namespace isce {
    namespace extension {

        // protect image methods
        namespace image {
            // image factory
            extern const char * const newImage_float__name__;
            extern const char * const newImage_float__doc__;
            PyObject * newImage_float(PyObject *, PyObject *);

            // view factory
            extern const char * const newView_float__name__;
            extern const char * const newView_float__doc__;
            PyObject * newView_float(PyObject *, PyObject *);
        } // of namespace image

    } // of namespace extension`
} // of namespace isce

#endif

// end of file
