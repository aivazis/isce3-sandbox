# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#


# support
import isce


# the ISCE plexus
class ISCE(isce.plexus, family='isce.components.isce'):
    """
    The main action dispatcher for the isce application
    """

    # types
    from .Action import Action as pyre_action


    # support for the help system
    def pyre_banner(self):
        """
        Place the application banner in the {info} channel
        """
        # grab the info channel
        info = self.info
        # make some space
        info.line()
        # get the help header
        info.line(isce.version.license)
        # all done
        return


# end of file
