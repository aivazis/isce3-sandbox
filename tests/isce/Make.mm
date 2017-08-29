# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# package defaults
include isce.def

# the subdirectories to visit
RECURSE_DIRS = \
    srtm \


# standard targets
all: test clean

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

# test targets
test: sanity low-level
	BLD_ACTION="test" $(MM) recurse

sanity:
	${PYTHON} ./sanity.py

low-level:
	${PYTHON} ./extension.py

# end of file
