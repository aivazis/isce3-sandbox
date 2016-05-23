# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# orthologue
# (c) 1998-2015 all rights reserved
#


# externals
import isce


# declaration
class SRTM(isce.panel(), family='isce.actions.srtm'):
    """
    Manage the local cache of SRTM elevation tiles
    """


    # user configurable state
    archive = isce.topography.archive(default=isce.topography.srtm())
    archive.doc = 'the elevation model archive manager'

    region = isce.properties.array()
    region.doc = 'an array of (lat, lon) pairs of interest'

    force = isce.properties.bool(default=False)
    force.doc = 'perform the requested action unconditionally'


    @isce.export(tip="download the tiles that cover the region of interest")
    def plan(self, plexus, **kwds):
        """
        Describe the workplan to build an elevation model for the region of interest
        """
        # get the SRTM accessor
        srtm = self.archive
        # adjust its configuration
        srtm.cache = isce.primitives.path('etc', 'topography')
        # and ask it to estimate the work load
        srtm.plan()
        # all done
        return


    @isce.export(tip="download the tiles that cover a cloud of points")
    def download(self, plexus, **kwds):
        """
        Download tiles from the SRTM archive

        The {region} of interest is specified as a cloud of (lat, lon) pairs. This command
        computes the bounding box the points, and downloads all the tiles necessary to cover it
        """
        # grab the error channel
        error = plexus.error
        # complain
        error.log('download: not implemented yet')
        # all done
        return


# end of file
