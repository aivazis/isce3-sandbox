# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# package name
PACKAGE = topography
# the python modules
EXPORT_PYTHON_MODULES = \
    DEM.py \
    SRTM.py \
    SRTMMosaic.py \
    SRTMTile.py \
    __init__.py

# standard targets
all: export

export:: export-package-python-modules

live: live-package-python-modules

# end of file
