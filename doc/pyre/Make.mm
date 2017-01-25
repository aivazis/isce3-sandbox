# -*- Makefile -*-
#
# michael a.g. aïvázis
# orthologue
# (c) 1998-2017 all rights reserved
#

PROJECT = isce
PACKAGE = doc/pyre

OTHERS = \

DOCUMENT = pyre

PACKAGES =

INCLUDES = \
    config/*.sty \
    config/*.tex \

SECTIONS = \
    sections/*.tex \
    sections/*.bib \

LISTINGS = \
    listings/*.py \
    listings/*.pfg listings/*.cfg listings/*.pml \

FIGURES = \
    figures/*.pdf \

#
all: $(DOCUMENT).pdf

# preview types
osx: $(DOCUMENT).pdf
	open $(DOCUMENT).pdf

xpdf: $(DOCUMENT).pdf
	xpdf -remote $(DOCUMENT) $(DOCUMENT).pdf

# make the document using the default document class
$(DOCUMENT).pdf: $(DOCUMENT).tex $(PACKAGES) $(INCLUDES) $(SECTIONS) $(LISTINGS) $(FIGURES)

# housekeeping
PROJ_CLEAN += $(CLEAN_LATEX) *.snm *.nav *.vrb *.lbf
PROJ_DISTCLEAN = *.ps *.pdf $(PROJ_CLEAN)

# end of file
