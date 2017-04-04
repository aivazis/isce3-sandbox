# -*- Makefile -*-
#
# michael a.g. aïvázis
# orthologue
# (c) 1998-2017 all rights reserved
#

PROJECT = isce
PACKAGE = doc/pyre

# the documents in this package
DOCUMENTS = overview
# the default document to build; override from the environment
DOCUMENT = overview

# the configuration dependencies
CONFIG = \
    config/*.sty \
    config/*.tex \

# section bodies
SECTIONS = \
    sections/*.tex \
    sections/*.bib \

# source code listings
LISTINGS = \
    listings/*.py \
    listings/*.pfg listings/*.cfg listings/*.pml \

# figures
FIGURES = \
    figures/*.pdf \

# make everything
all: $(DOCUMENTS)

# the documents
overview: overview.pdf

# explcit targets
overview.pdf: overview.tex $(CONFIG) $(SECTIONS) $(LISTINGS) $(FIGURES)

# preview types
osx: $(DOCUMENT).pdf
	open $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# housekeeping
PROJ_CLEAN += $(CLEAN_LATEX) *.snm *.nav *.vrb *.lbf
PROJ_DISTCLEAN = *.ps *.pdf $(PROJ_CLEAN)

# end of file
