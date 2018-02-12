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
    corr_flag.c \
    grass.c \
    residue.c \
    trees.c \

# the default target compiles this library and exports it
all: export-package-headers $(PROJ_DLL) export-libraries


# end of file
