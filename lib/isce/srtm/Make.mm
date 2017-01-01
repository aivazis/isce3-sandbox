# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# project defaults
include isce.def
# the name of the package
PACKAGE = srtm

# the sources
PROJ_SRCS =
# the products
PROJ_SAR = $(BLD_LIBDIR)/lib$(PROJECT).$(EXT_SAR)
PROJ_DLL = $(BLD_LIBDIR)/lib$(PROJECT).$(EXT_SO)
# the private build space
PROJ_TMPDIR = $(BLD_TMPDIR)/${PROJECT}/lib/$(PROJECT)
# what to clean
PROJ_CLEAN += $(EXPORT_INCDIR)/$(PACKAGE)

# what to export
# the library
EXPORT_LIBS = $(PROJ_DLL)
# the package headers
EXPORT_PKG_HEADERS = \
    AvailabilityMap.h AvailabilityMap.icc \
    Tile.h Tile.icc \
    public.h

# the standard targets
all: export

export:: export-package-headers

# end of file
