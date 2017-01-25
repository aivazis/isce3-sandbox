#!/usr/bin/env python3
import isce #@\label{line:applications-simple-import}@

# the app declaration
class Stitcher(isce.application): #@\label{line:applications-simple-decl}@
    """
    Stitch together a digital elevation model for a region of interest
    """

    # user configurable state
    dem = isce.topography.dem() #@\label{line:applications-simple-dem}@
    dem.doc = 'the assembler of the elevation model'

    # behaviors
    @isce.export
    def main(self, *args, **kwds): #@\label{line:applications-simple-main}@
        """The main entry point"""
        # stitch the dem
        self.dem.stitch() #@\label{line:applications-simple-stitch}@
        # indicate that all went well
        return 0

# main
if __name__ == '__main__': #@\label{line:applications-simple-boot}@
    app = Stitcher(name='stitch')
    status = app.run()
    raise SystemExit(status)

# end of file
