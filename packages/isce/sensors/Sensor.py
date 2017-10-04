# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# get the package
import isce


# the digital elevation model protocol
class Sensor(isce.protocol, family='isce.sensors'):
    """
    Requirements for components that encapsulate instruments
    """

    # user configurable state


    # framework obligations
    @classmethod
    def pyre_default(cls, **kwds):
        """
        Supply a default device
        """
        # nothing yet
        return None


# end of file
