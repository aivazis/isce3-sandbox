# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis
# orthologue
# (c) 1998-2016 all rights reserved
#


# base class
from pyre.nexus.Crew import Crew


# the task that fetches tiles from the SRTM archive
class Downloader(Crew):
    """
    Download tiles from the SRTM archive
    """

    # types
    from .Availability import Availability as tilecodes


    # interface
    def engage(self, task, **kwds):
        """
        Download a tile
        """
        # sign in
        # my tasks are tiles
        tile = task
        # alias the task availability enum
        codes = self.tilecodes
        # grab the availability map
        map = self.map
        # look up my tile
        map.getTileAvailability(tile=tile)

        # if the tile is known to not exist
        if tile.status is codes.unavailable:
            print("{.pid}: tile {.name} is unavailable".format(self, tile))
            # not much else to do
            return 0

        # if the tile is already cached locally
        if tile.status is codes.cached:
            print("{.pid}: tile {.name} is already cached".format(self, tile))
            # all done
            return 0

        # otherwise, gingerly...
        try:
            # go get it
            data = tile.download()
        # if anything goes wrong
        except Exception as error:
            # NYI
            print("tile {.name}: {}".format(tile, error))
            raise

        # update the map
        map.update(tile=tile)

        # if the status is now {unavailable}
        if tile.status is codes.unavailable:
            print("{.pid}: tile {.name} is unavailable".format(self, tile))
            # we are done
            return 0

        # otherwise, cache it
        tile.write(cache=self.cache, contents=data)
        # and update the map once more
        map.update(tile=tile)

        print("{.pid}: tile {.name} is now cached".format(self, tile))

        # indicate success
        return 0


    # meta-methods
    def __init__(self, cache, map, **kwds):
        # chain up
        super().__init__(**kwds)
        # save the location of the local archive
        self.cache = cache
        # and the availability map
        self.map = map
        # all done
        return


# end of file
