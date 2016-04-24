# -*- Makefile -*-
#
# michael a.g. aïvázis
# parasim
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def
# the name of the package
PACKAGE = image

# the package headers
EXPORT_PKG_HEADERS = \
    Index.h Index.icc \
    Layout.h Layout.icc \
    Shape.h Shape.icc \
    Tile.h Tile.icc \

# the standard targets
all: export

export:: export-package-headers

# end of file
