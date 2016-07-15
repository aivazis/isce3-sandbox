# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# the digital elevation model protocol
class DEM(isce.protocol, family='isce.topography'):
    """
    Requirements for accessors of digital elevation model archives
    """

    # user configurable state
    region = isce.properties.array()
    region.doc = 'the specification of the region of interest'


    # framework obligations
    @classmethod
    def pyre_default(cls, **kwds):
        """
        Supply a default DEM archive
        """
        # the default is
        from .srtm3 import archive as default
        # so return it
        return default


# end of file
