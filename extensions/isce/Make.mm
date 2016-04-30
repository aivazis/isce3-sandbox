# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# the package
PACKAGE = extensions
# the module
MODULE = isce
# build a python extension
include std-pythonmodule.def

# adjust the build parameters
PROJ_LCXX_LIBPATH=$(BLD_LIBDIR)
# the list of extension source files
PROJ_SRCS = \
    exceptions.cc \
    metadata.cc \
# the private build space
PROJ_TMPDIR = $(BLD_TMPDIR)/${PROJECT}/extensions/isce
# my dependencies
PROJ_LIBRARIES += -lisce -ljournal $(LCXX_FORTRAN)

# register the dependence on {libisce} so I get recompiled when it changes
PROJ_OTHER_DEPENDENCIES = $(BLD_LIBDIR)/libisce.$(EXT_SO)

# the pile of things to clean
PROJ_CLEAN += \
    $(PROJ_CXX_LIB) \
    $(MODULE_DLL) \
    $(EXPORT_BINDIR)/$(MODULE)$(MODULE_SUFFIX)

# end of file
