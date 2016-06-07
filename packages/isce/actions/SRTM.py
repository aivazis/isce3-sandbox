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

    The SRTM tiles necessary to assemble digital elevation models are kept in a local
    cache. Subsequent processing that requires these tiles can be serviced from your disk,
    saving a trip to the USGS server.

    You can get information about your local store by issuing the 'sync' command, which
    will tell you where the store is and generate a report of its current contents.

    If you know your region of interest, you can ask for a work plan, to get a feeling for
    which tiles cover it and their status. You can also download them to avoid network
    traffic during later processing. Regions of interest are formed by computing the
    bounding box of a list of (lat, lon) pairs.
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
    @isce.export(tip="sync the availability map with the contents of the local cache ")
    def sync(self, plexus, **kwds):
        """
        Ensure that the availability map reflects the contents of the local store accurately
        """
        # pick a channel
        channel = plexus.info
        # sign in
        channel.line('syncing the local availability map')
        # get my data store manager
        srtm = self.srtm
        # and ask it to make a plan
        status = srtm.sync(channel=channel, dent=1)
        # flush the channel
        channel.log()
        # and return the status code
        return status


    @isce.export(tip="make a workplan for assembling the elevation model for the given region")
    def plan(self, plexus, **kwds):
        """
        Describe the workplan to build an elevation model for the region of interest
        """
        # pick a channel
        channel = plexus.info
        # sign in
        channel.line('making a work plan')
        # get my data store manager
        srtm = self.srtm
        # and ask it to make a plan
        status = srtm.plan(channel=channel, dent=1)
        # flush the channel
        channel.log()
        # and return the status code
        return status


    @isce.export(tip="download the tiles that cover a cloud of points")
    def download(self, plexus, **kwds):
        """
        Download tiles from the SRTM archive

        The {region} of interest is specified as a cloud of (lat, lon) pairs. This command
        computes the bounding box the points, and downloads all the tiles necessary to cover it
        """
        # pick a channel
        channel = plexus.info
        # sign in
        channel.line('retrieving tiles')
        # get my data store manager
        srtm = self.srtm
        # and ask it to make a plan
        status = srtm.download(channel=channel)
        # flush the channel
        channel.log()
        # and return the status code
        return status


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
