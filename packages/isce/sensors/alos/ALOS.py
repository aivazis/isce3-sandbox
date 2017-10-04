# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# get the package
import isce


# support for the ALOS instrument
class ALOS(isce.component,
           family='isce.sensors.ALOS', implements=isce.sensor):
    """
    Encapsulation of the ALOS instrument
    """


# end of file
