# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2017 all rights reserved
#

# pull the framework parts
from pyre import (
    # protocols, components and traits
    schemata, protocol, component, foundry, properties, constraints, application,
    # decorators
    export, provides,
    # the runtime manager
    executive,
    # miscellaneous packages
    geometry, patterns, primitives, timers, tracking, units,
    # support for asynchrony
    nexus,
    # plexus support
    action, command, panel, plexus, application
    )
# grab the journal
import journal

# fire up
package = executive.registerPackage(name='isce', file=__file__)
# save the geography
home, prefix, defaults = package.layout()

# export my parts
from . import (
    exceptions,     # version info
    version,        # version info
    extensions,     # my extension module

    # support
    topography,     # digital elevation models

    # user interface
    components, actions,
    )

# end of file
