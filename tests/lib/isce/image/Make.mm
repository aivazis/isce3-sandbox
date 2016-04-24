# -*- Makefile -*-
#
# michael a.g. aïvázis
# parasim
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def

TESTS = \
    tile \
    tile-band \
    tile-line \
    tile-pixel \

# the standard targets
all: test clean

test: $(TESTS)
	@echo "testing:"
	@for testcase in $(TESTS); do { \
            echo "    $${testcase}" ; ./$${testcase} || exit 1 ; \
            } done

# build
PROJ_CLEAN = $(TESTS)
PROJ_LIBRARIES = -ljournal
LIBRARIES = $(PROJ_LIBRARIES) $(EXTERNAL_LIBS)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@ $(LCFLAGS) $(LIBRARIES)

%: %.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LCXXFLAGS) $(LIBRARIES)

# end of file
