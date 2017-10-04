#! /usr/bin/env python3
# -*- coding: utf-8 -*-
#
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

"""
Verify that the ALOS sensor can be bound to an app
"""

# get the module
import isce

# make an app
class Harness(isce.application, family='isce.application.harness'):
    """
    A simple sensor harness with ALOS as the default instrument
    """

    # user configurable state
    sensor = isce.sensor(default='ALOS')
    sensor.doc = 'encapsulation of the instrument'

    # behavior
    @isce.export
    def main(self, *args, **kwds):
        """
        The main entry point
        """
        # pick a channel
        channel = self.debug
        # show me
        channel.line('alos.py')
        channel.line('  sensor: {}'.format(self.sensor))
        channel.line('          {}'.format(self.pyre_where('sensor')))
        # flush
        channel.log()

        # pull the ALOS support directly from its home
        from isce.sensors.alos.ALOS import ALOS
        # check
        assert isinstance(self.sensor, ALOS)

        # all done
        return 0


# bootstrap
if __name__ == "__main__":
    # instantiate
    app = Harness(name='harness')
    # invoke
    status = app.run()
    # share
    raise SystemExit(status)


# end of file
