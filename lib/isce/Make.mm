# -*- Makefile -*-
#
# michael a.g. aïvázis
# parasim
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# my dibdirectories
RECURSE_DIRS = \
    image \

# the top level headers
EXPORT_HEADERS = \
    image.h

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
