# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# the digital elevation model protocol
class SRTM(isce.component, family='isce.topography.srtm', implements=isce.topography.archive):
    """
    Accessor for the SRTM data archive
    """

    # user configurable state
    region = isce.properties.array()
    region.doc = 'the specification of the region of interest'


    # protocol obligations
    @isce.export
    def fetch(self):
        """
        Retrieve
        """


# end of file
