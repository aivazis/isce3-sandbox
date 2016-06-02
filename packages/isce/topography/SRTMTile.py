# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#


# externals
import enum


# declaration
class SRTMTile:
    """
    Encapsulation of an SRTM tile
    """

    # public data
    point = None      # a (lat, lon) pair that locates the SW corner of the tile
    resolution = None # the number of arcseconds per pixel


    @property
    def name(self):
        """
        The canonical name of the tile, generated from its reference pixel
        """
        # first check the cache
        name = self._name
        # if it has a valid value
        if name:
            # send it off
            return name
        # otherwise, unpack the reference pixel
        lat, lon = self.point
        # build the canonical name
        name = '{}{:02}{}{:03}'.format(
            "N" if lat >=0 else "S", abs(lat),
            "E" if lon >= 0 else "W", abs(lon))
        # cache it
        self._name = name
        # and return it
        return name


    @property
    def filename(self):
        """
        The canonical name for the file that contains the tile grid
        """
        # easy...
        return self._filenameTemplate.format(self)


    @property
    def uriUSGS(self):
        """
        Build the address for this tile at the USGS data store
        """
        # easy...
        return self._usgs.format(self)


    @property
    def isCached(self):
        """
        Check whether this tile is marked as locally cached
        """
        # check my status
        return self.status == self.Status.cached


    @isCached.setter
    def isCached(self, flag):
        """
        Set whether this tile is marked as locally cached
        """
        # if we know for sure
        if flag is True:
            # update my status
            self.status = self.Status.cached
        # all done
        return


    # meta-methods
    def __init__(self, point, hires=True, status=None, **kwds):
        # chain up
        super().__init__(**kwds)
        # record the reference pixel
        self.point = point
        # and the resolution
        self.resolution = 1 if hires else 3 # arcseconds per pixel
        # deduce the status of the tile; see the enum definition below
        self.status = self.Status.unknown if status is None else status
        # all done
        return


    # private data
    # cache for the canonical name
    _name = None

    # constants
    # the template for the URI of the datastore at the USGS
    _usgs = 'http://e4ftl01.cr.usgs.gov/SRTM/SRTMGL{0.resolution}.003/2000.02.11/'
    # the tile URI template: tile name and resolution
    _filenameTemplate = "{0.name}.SRTMGL{0.resolution}.hgt.zip"


    # tile status
    @enum.unique
    class Status(enum.Enum):
        """
        Tile status codes
        """
        unknown = 1 # we have never attempted to get this tile, so we know nothing about it
        unavailable = 2 # we know for a fact that the SRTM data set does not include this tile
        available = 3 # we know for a fact that the SRTM data set includes this tile
        cached = 4 # we have a local copy of this tile


# end of file
