# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# the name of the package
PACKAGE = image

# the products
PROJ_SAR = $(BLD_LIBDIR)/lib$(PROJECT).$(EXT_SAR)
PROJ_DLL = $(BLD_LIBDIR)/lib$(PROJECT).$(EXT_SO)
# the sources
PROJ_SRCS = \
    Direct.cc \
# the private build space
PROJ_TMPDIR = $(BLD_TMPDIR)/${PROJECT}/lib/$(PROJECT)
# what to clean
PROJ_CLEAN += $(EXPORT_INCDIR)/$(PACKAGE)

# what to export
# the library
EXPORT_LIBS = $(PROJ_DLL)
# the package headers
EXPORT_PKG_HEADERS = \
    Direct.h Direct.icc \
    Index.h Index.icc \
    Iterator.h Iterator.icc \
    Layout.h Layout.icc \
    Tile.h Tile.icc \


# the standard targets
all: $(PROJ_DLL) export
	echo $(PROJ_DLL)

export:: export-package-headers export-libraries

# end of file
