# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# project defaults
include isce.def

# the pile of tests
TESTS = \
    tile \
    tile-band \
    tile-line \
    tile-pixel \
    tile-maps \
    direct-create \
    direct-map \
    direct-instantiate \

# tests that should fail because their access patterns are prohibited
SHOULD_FAIL = \
    direct-clone \

# the standard targets
all: test clean

# testing
test: $(TESTS)
	@echo "testing:"
	@for testcase in $(TESTS); do { \
            echo "    $${testcase}" ; ./$${testcase} || exit 1 ; \
            } done

# build
PROJ_CLEAN += $(TESTS) image.dat
PROJ_LIBRARIES = -lisce -ljournal
LIBRARIES = $(PROJ_LIBRARIES) $(EXTERNAL_LIBS)

%: %.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LCXXFLAGS) $(LIBRARIES)

# end of file
