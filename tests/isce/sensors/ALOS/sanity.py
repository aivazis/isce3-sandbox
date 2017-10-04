#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

"""
Sanity check: verify that the package is accessible
"""

def test():
    # get the module
    import isce
    # verify that the ALOS foundry is available
    assert isce.sensors.ALOS
    # all done
    return


# main
if __name__ == "__main__":
    test()

# end of file
