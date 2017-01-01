# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# project defaults
include isce.def
# my subdirectories
RECURSE_DIRS = \
    image \
    srtm \

# the products
PROJ_SAR = $(BLD_LIBDIR)/lib$(PROJECT).$(EXT_SAR)
PROJ_DLL = $(BLD_LIBDIR)/lib$(PROJECT).$(EXT_SO)
# the private build space
PROJ_TMPDIR = $(BLD_TMPDIR)/${PROJECT}/lib/$(PROJECT)
# the sources
PROJ_SRCS = \
    version.cc \

# what to clean
PROJ_CLEAN += $(EXPORT_LIBS) $(EXPORT_INCDIR)

# what to export
# the library
EXPORT_LIBS = $(PROJ_DLL)
# the top level headers
EXPORT_HEADERS = \
    image.h \
    isce.h \
    srtm.h \
    version.h \

# get today's date
TODAY = ${strip ${shell date -u}}
# grab the revision number
REVISION = ${strip ${shell bzr revno}}
# if not there
ifeq ($(REVISION),)
REVISION = 0
endif

# the standard targets
all: export

tidy::
	BLD_ACTION="tidy" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

distclean::
	BLD_ACTION="distclean" $(MM) recurse

export:: version.cc $(PROJ_DLL) export-headers export-libraries
	BLD_ACTION="export" $(MM) recurse
	@$(RM) version.cc

revision: version.cc $(PROJ_DLL) export-libraries
	@$(RM) version.cc

# construct my {version.cc}
version.cc: version Make.mm
	@sed \
          -e "s:MAJOR:$(PROJECT_MAJOR):g" \
          -e "s:MINOR:$(PROJECT_MINOR):g" \
          -e "s:REVISION:$(REVISION):g" \
          -e "s|TODAY|$(TODAY)|g" \
          version > version.cc

live:
	BLD_ACTION="live" $(MM) recurse

# end of file
