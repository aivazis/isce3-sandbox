#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

"""
Sanity check: verify that the SRTM component is accessible
"""

def test():
    # get the component
    from isce.topography.SRTM import SRTM
    # access the component factory
    srtm = SRTM(name='srtm')

    # assemble the configuration
    doc = '\n'.join(srtm.pyre_showConfiguration())
    # grab the journal
    import journal
    # make a channel and show me the configuration
    journal.debug("isce.topography").log(doc)

    # all done
    return


# main
if __name__ == "__main__":
    test()

# end of file
