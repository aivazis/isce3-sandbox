# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def

PACKAGE = etc/$(PROJECT)/topography
# the exportables
EXPORT_ETC =
# add my target folder to the clean up list
PROJ_CLEAN += $(EXPORT_ETCDIR)

# the standard targets
all: export

export:: $(EXPORT_ETCDIR)

live: live-dirs

# end of file
