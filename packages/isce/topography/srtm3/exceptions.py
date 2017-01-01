# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# orthologue
# (c) 2003-2017 all rights reserved
#

"""
Definitions for all the exceptions raised by this package
"""


# pull the base class
from isce.exceptions import ISCEError


# my local error types
class AuthenticationError(ISCEError):
    """
    Exception raised when there is something wrong with the user's credentials
    """

    # public data
    description = "{0.reason}"

    # meta-methods
    def __init__(self, reason, **kwds):
        # chain up
        super().__init__(**kwds)
        # save the cause of the error
        self.reason = reason
        # all done
        return


# end of file
