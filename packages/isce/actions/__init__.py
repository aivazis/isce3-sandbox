# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# administrivia
@isce.foundry(implements=isce.action, tip="display information about this application")
def about():
    """
    Display information about this application
    """
    # get the record
    from .About import About
    # and return it
    return About


# end of file
