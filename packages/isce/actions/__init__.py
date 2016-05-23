# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# topography
@isce.foundry(implements=isce.action, tip="download and assemble digital elevation models")
def dem():
    """
    Display information about this application
    """
    # get the command panel
    from .Topography import Topography
    # and return it
    return Topography


@isce.foundry(implements=isce.action, tip="manage the local cache of the SRTM data store")
def srtm():
    """
    Display information about this application
    """
    # get the command panel
    from .SRTM import SRTM
    # and return it
    return SRTM


# administrivia
@isce.foundry(implements=isce.action, tip="display information about this application")
def about():
    """
    Display information about this application
    """
    # get the command panel
    from .About import About
    # and return it
    return About


# end of file
