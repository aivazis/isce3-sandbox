# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# the digital elevation model protocol
class SRTM(isce.component, family='isce.dem.srtm', implements=isce.dem.archive):
    """
    The protocol implemented by digital elevation model constructors
    """

# end of file
