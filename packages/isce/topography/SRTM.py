# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce
# externals
import itertools, math


# the digital elevation model protocol
class SRTM(isce.component, family='isce.topography.srtm', implements=isce.topography.archive):
    """
    Accessor for the SRTM data archive
    """

    # user configurable state
    region = isce.properties.array()
    region.doc = 'the specification of the region of interest'

    hires = isce.properties.bool(default=True)
    hires.doc = 'select the model resolution'


    # protocol obligations
    @isce.export
    def download(self):
        """
        Retrieve the tiles necessary to cover the convex hull of my {region}
        """
        # go through the tile URIs
        for uri in self.uris():
            # show me
            print(uri)

        # all done
        return


    # convenience interface
    def uris(self):
        """
        Build a sequence of {uri}s that point to the tiles that cover my region
        """
        # build a mosaic that covers my {region}
        mosaic = self.mosaic()
        # assemble their names
        names = self.tileNames(mosaic)
        # build the pile of tile URIs and return them to the caller
        return self.tileURIs(names)


    # implementation details
    def mosaic(self):
        """
        Build a mosaic of SRTM tiles that cover the bounding box of the points in my {region} of
        interest
        """
        # get the region of interest
        region = self.region
        # if the user has not specified one
        if not region:
            # the mosaic is empty
            return []
        # otherwise, compute the bounding box of all the points in my {region}
        low = []
        high = []
        #  the SRTM data are in 1x1 degree tiles, so we keep the integer part of the
        # coördinates
        for axis in zip(*region):
            # store the minimum in {low}
            low.append(math.floor(min(axis)))
            # and one more than the maximum in {high}, so we can form a range that covers the
            # desired tiles
            high.append(math.floor(max(axis))+1)

        # form the mosaic by building the cartesian product of the ranges and return it
        return itertools.product(*(range(*limits) for limits in zip(low,high)))


    def tileNames(self, mosaic):
        """
        Given a sequence of (lat, lon) pairs, return a sequence of SRTM tile names
        """
        # go through each tile
        for tile in mosaic:
            # unpack
            lat, lon = tile
            # build the name of the tile; numeric fields are zero padded to three digits
            name = '{}{:02}{}{:03}'.format(
                "N" if lat >=0 else "S", abs(lat),
                "E" if lon >= 0 else "W", abs(lon))
            # hand the name to the caller
            yield name

        # all done
        return


    def tileURIs(self, names):
        """
        Build a sequence of the tile URIs from their names
        """
        # grab the uri template
        uri = self.uri
        # decide whether we are looking for the low or high resolution images
        resolution = 1 if self.hires else 3
        # go through each name
        for name in names:
            # form the uri and hand itoff
            yield uri.format(name, resolution)

        # all done
        return


    # constants
    # the tile URI template: tile name and resolution
    uri = 'http://e4ftl01.cr.usgs.gov/SRTM/SRTMGL{1}.003/2000.02.11/{0}.SRTMGL{1}.hgt.zip'


# end of file
