# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# get the package
import isce

# grab the protocol
from .Sensor import Sensor as sensor


# SRTMv3 support
@isce.foundry(implements=sensor, tip='the ALOS instrument')
def ALOS():
    """
    Encapsulation of the ALOS instrument
    """
    # grab the factory
    from . import alos
    # and return it
    return alos.sensor


# end of file
