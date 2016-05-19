# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# orthologue
# (c) 1998-2015 all rights reserved
#


# externals
import isce


# declaration
class Topography(isce.panel(), family='isce.actions.dem'):
    """
    Download and assemble digital elevation models
    """


    # user configurable state
    archive = isce.topography.archive()
    archive.doc = 'the elevation model archive manager'

    region = isce.properties.array()
    region.doc = 'an array of (lat, lon) pairs of interest'


    @isce.export(tip="download the tiles that cover the region of interest")
    def download(self, plexus):
        """
        Download digital elevation models from an archive
        """
        # get the archive accessor
        archive = self.archive
        # configure it
        archive.region = self.region
        # and ask it to do the work
        archive.download()
        # all done
        return


# end of file
