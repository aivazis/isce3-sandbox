# -*- coding: utf-8 -*-

# support
import isce

# the action implementation
class say(isce.command(), family='isce.actions.say'):
    """
    An example of a custom action provided by the end user
    """

    # constants
    pyre_tip = 'an example of a custom action provided by the end user'

    # behavior
    @isce.export
    def main(self, plexus, **kwds):
        """
        A custom behavior
        """
        # say something
        plexus.info.log("hello world!")
        # all done
        return 0

# end of file
