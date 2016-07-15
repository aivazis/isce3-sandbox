# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce

# grab the protocol
from .DEM import DEM as archive


# SRTMv3 support
@isce.foundry(implements=archive)
def srtm():
    """
    Component that assembles digital elevation models from SRTM tiles
    """
    # grab the factory
    from . import srtm3
    # and return it
    return srtm3.archive


# end of file
