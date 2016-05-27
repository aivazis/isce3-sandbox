# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# my subdirectories
RECURSE_DIRS = \
    grid \
    image \

# the top level headers
EXPORT_HEADERS = \
    grid.h \
    image.h \
    isce.h \
    version.h \

# adjustments to the project settings
PROJ_CLEAN += $(EXPORT_INCDIR)

# the standard targets
all: export
	BLD_ACTION="all" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

export:: export-headers
	BLD_ACTION="export" $(MM) recurse

live:
	BLD_ACTION="live" $(MM) recurse

# end of file
