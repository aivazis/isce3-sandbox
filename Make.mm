# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# my subdirectories
RECURSE_DIRS = \
    lib \
    extensions \
    packages \
    tests \

# the standard targets
all:
	BLD_ACTION="all" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

export::
	BLD_ACTION="export" $(MM) recurse

live:
	BLD_ACTION="live" $(MM) recurse

pull:
	bzr pull bzr+ssh://$(PROJECT)@$(PROJ_REPO_HOST)

push:
	bzr push bzr+ssh://$(PROJECT)@$(PROJ_REPO_HOST)

# end of file
