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
    srtm = isce.topography.archive(default=isce.topography.srtm())
    srtm.doc = 'the elevation model archive manager'

    region = isce.properties.array()
    region.doc = 'an array of (lat, lon) pairs of interest'

    resolution = isce.properties.int(default=1)
    resolution.doc = 'the resolution of the data set in pixels per arc-second; either 1 or 3'

    force = isce.properties.bool(default=False)
    force.doc = 'perform the requested action unconditionally'


    # commands
    @isce.export(tip="download the tiles that cover the region of interest")
    def plan(self, plexus, **kwds):
        """
        Describe the workplan to build an elevation model for the region of interest
        """
        # get my data store manager
        srtm = self.srtm
        # and ask it to make a plan
        return srtm.plan(channel=plexus.info)


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


    # meta-methods
    def __init__(self, plexus, **kwds):
        # chain up
        super().__init__(plexus=plexus, **kwds)
        # grab the plexus private file space
        pfs = plexus.pfs

        # get my data store manager
        srtm = self.srtm

        # establish the location of the data store
        # the default location of the data set is derived from the manager family name
        cache = srtm.pyre_familyFragments()
        # if the store manager has the proper pedigree
        if cache:
            # derive the location of the data store from its name by dropping the package name
            uri = isce.primitives.path(cache[1:])
            # access it; careful not to look too deeply just in case there is a lot of data
            # cached here
            topostore = pfs['etc'].mkdir(uri).discover(levels=1)
            # attach it
            srtm.cache = topostore

        # pass on the region
        srtm.region = self.region
        # and the desired resolution
        srtm.resolution = self.resolution

        # all done
        return


# end of file
