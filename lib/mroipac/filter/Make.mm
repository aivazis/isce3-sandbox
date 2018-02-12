# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2018 all rights reserved
#

# get the global defaults
include isce.def

# the local package: everything goes to {libmroipac}
PACKAGE = mroipac

# the products
PROJ_SAR = $(BLD_LIBDIR)/lib$(PACKAGE).$(EXT_SAR)
PROJ_DLL = $(BLD_LIBDIR)/lib$(PACKAGE).$(EXT_SO)
# the private build space
PROJ_TMPDIR = $(BLD_TMPDIR)/${PROJECT}/lib/$(PACKAGE)
# what to export
EXPORT_LIBS = $(PROJ_DLL)

# the list of sources to compile
PROJ_SRCS = \
    cpx2mag_phs.c \
    mag_phs2cpx.c \
    psfilt.c \
    rescale_magnitude.c \
    timing.c \

# clean up
PROJ_CLEAN += $(EXPORT_LIBS) $(EXPORT_INCDIR)

# the default target compiles this library and exports it
all: export-package-headers $(PROJ_DLL) export-libraries


# end of file
