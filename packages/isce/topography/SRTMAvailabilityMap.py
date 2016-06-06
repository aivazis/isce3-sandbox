# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# get the package
import isce


# the tile availability mpa
class SRTMAvailabilityMap:
    """
    The tile availability map
    """

    # types
    from .SRTMAvailability import SRTMAvailability as availability


    # interface
    def sync(self, cache, mosaic, channel=None, indent=1):
        """
        Sync my contents with the contents of the local {cache} for the tiles in {mosaic}
        """
        # make a channel
        channel = self._channel if channel is None else channel
        # setup the margin
        margin = '  '*indent

        # now visit all the tiles in the globe
        for tile in mosaic:
            # check whether the tile exists in the local store
            isCached = tile.name in cache
            # fetch the map status of this tile
            status = self.check(tile=tile)

            # do the update
            # if the file is in the local store but the map doesn't know it
            if isCached and status is not self.availability.cached:
                # mark it in the map
                self.mark(tile=tile, status=self.availability.cached)
                # and show me
                channel.line('{}marked tile {tile.name!r} as locally available'.format(
                    margin, tile=tile))

            # if the file is marked as cached in the map but it's not in the store contents
            if status is self.availability.cached and not isCached:
                # update the map
                self.mark(tile=tile, status=self.availability.unknown)
                # and show me
                channel.line('{}tile {tile.name!r} has disappeared'.format(margin, tile=tile))

        # all done
        return


    def summary(self, channel=None, indent=1):
        """
        Produce a tile availability summary
        """
        # make a channel
        channel = self._channel if channel is None else channel
        # setup the margin
        margin = '  '*indent
        # sign in
        channel.line('{}tile availability summary:'.format(margin))

        # get my map
        map = self.map
        # and compute the range of status values
        range = len(self.availability)
        # build the summary
        frequencies = isce.extensions.isce.srtmAvailabilityMapSummary(map, range)

        # display the table: go through the status codes
        for status in self.availability:
            # label
            label = status.name
            # compute the count
            count = frequencies[status.value]
            # why not do it right...
            plural = '' if count == 1 else 's'
            # show me
            channel.line('{}  {}: {} tile{}'.format(margin, label, count, plural))

        # all done
        return frequencies


    # individual tile status access
    def check(self, tile):
        """
        Check the availability of the given tile
        """
        # get its location
        index = tile.point
        # get the status from my map
        value = isce.extensions.isce.srtmAvailabilityMapGet(self.map, index)
        # convert it into an availability code and return it
        return tuple(self.availability)[value]


    def mark(self, tile, status):
        """
        Adjust the status of the given tile
        """
        # get its location
        index = tile.point
        # get the status value
        value = status.value
        # set the status in my map and return it
        return isce.extensions.isce.srtmAvailabilityMapSet(self.map, index, status.value)


    # meta-methods
    def __init__(self, uri, **kwds):
        # chain up
        super().__init__(**kwds)
        # save my path
        self.uri = uri
        # make the capsule
        self.map = isce.extensions.isce.srtmAvailabilityMap(str(uri))

        # make a default channel
        self._channel = isce.journal.info("isce.topography.srtm")

        # all done
        return


# end of file
