# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2018 all rights reserved
#

# get the global defaults
include isce.def

# the local package: everything goes to {libmroipac}
PACKAGE = mroipac
# the list of directories to visit
RECURSE_DIRS = \
    correlation \
    dopiq \
    doppler \
    filter \
    geolocate \
    grass \
    image \
    peg \
    slc \

# standard targets
all: subdirs

subdirs::
	BLD_ACTION="all" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

export::
	BLD_ACTION="export" $(MM) recurse

#  shortcuts to building in my subdirectories
.PHONY: $(RECURSE_DIRS)

$(RECURSE_DIRS):
	(cd $@; $(MM))

# end of file
