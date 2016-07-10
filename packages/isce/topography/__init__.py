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


# SRTM support
@isce.foundry(implements=archive)
def srtm():
    """
    Component that assembles digital elevation models from SRTM tiles
    """
    # grab the factory
    from .srtm.SRTM import SRTM
    # and return it
    return SRTM


# end of file
