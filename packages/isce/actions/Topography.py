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
    Download and assemble a digital elevation model for a region of interest
    """


    # user configurable state
    dem = isce.topography.dem()
    dem.doc = 'the digital elevation model assembler'

    region = isce.properties.array()
    region.doc = 'an array of (lat, lon) pairs of interest'

    force = isce.properties.bool(default=False)
    force.doc = 'perform the requested action unconditionally'


    @isce.export(tip="download the tiles that cover the region of interest")
    def download(self, plexus, **kwds):
        """
        Download digital elevation models from an archive
        """
        # pick a channel
        channel = plexus.info
        # get the archive accessor
        dem = self.dem
        # configure it
        dem.region = self.region
        # and ask it to do the work
        status = dem.download(channel=channel)
        # flush the channel
        channel.log()
        # all done
        return status


    @isce.export(tip="stitch together all necessary tiles to form the elevation model")
    def stitch(self, plexus, **kwds):
        """
        Assemble a digital elevation model by stitching together tiles from a data archive
        """
        # grab the error channel
        error = plexus.error
        # complain
        error.log('stitch: not implemented yet')
        # all done
        return


    # meta methods
    def __init__(self, plexus, **kwds):
        # chain up
        super().__init__(plexus=plexus, **kwds)

        # get my dem assembler
        dem = self.dem

        # pass on the region setting
        dem.region = self.region

        # grab the plexus private file space
        pfs = plexus.pfs
        # by convention, the location of the data cache is derived from the assmebler family
        # name by dropping it package name; get the family name
        family = dem.pyre_familyFragments()
        # if there is one
        if family:
            # derive the location of the data store
            uri = isce.primitives.path(family[1:])
            # access it, gingerly; there may be a lot of files here
            cache = pfs['etc'].mkdir(uri).discover(levels=1)
            # attach it
            dem.cache = cache

        # all done
        return


# end of file
