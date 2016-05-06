# -*- Makefile -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

include isce.def

all: test clean

test: sanity low-level

sanity:
	${PYTHON} ./sanity.py

low-level:
	${PYTHON} ./extension.py
	${PYTHON} ./extension_image.py
	${PYTHON} ./extension_view.py

# end of file
