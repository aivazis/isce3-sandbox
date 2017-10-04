# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# project defaults
include isce.def

# standard targets
all: test clean

test: sanity alos

sanity:
	${PYTHON} ./sanity.py

alos:
	${PYTHON} ./alos.py

# end of file
