#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

"""
Sanity check: verify that the low level image factory is accessible
"""

def test():
    # get the module
    import isce

    # access the low level image factory
    image = isce.extensions.isce.newImage_float()

    # all done
    return


# main
if __name__ == "__main__":
    test()

# end of file
