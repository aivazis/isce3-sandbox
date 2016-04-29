# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

include isce.def

all: test clean

test: sanity

sanity:
	${PYTHON} ./sanity.py
	${PYTHON} ./extension.py

# end of file
