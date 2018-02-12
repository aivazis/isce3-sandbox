# -*- Makefile -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2018 all rights reserved
#

# project defaults
include isce.def
# package name
PACKAGE = group
# add this to the clean pile
PROJ_CLEAN += authorized_keys
# the list of public keys
PUBLIC_KEYS = $(wildcard *.pub)

# standard targets
all: tidy
# make the autorized keys file
authorized_keys: $(PUBLIC_KEYS) grant.py grant.pfg Make.mm
	./grant.py

publish: authorized_keys
	$(SCP) $< $(PROJ_REPO_ADMIN)@$(PROJ_REPO_HOST):$(PROJ_REPO_HOME)/.ssh

live: publish clean

# end of file
