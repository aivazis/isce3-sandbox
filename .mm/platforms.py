# -*- Python -*-
# -*- coding: utf-8 -*-
#
# michael a.g. aïvázis <michael.aivazis@para-sim.com>
# (c) 2003-2016 all rights reserved
#

# externals
import os

# platform hook
def platform(builder):
    """
    Decorate the {builder} with platform specific options
    """
    # get the platform tag
    platform = builder.host.system

    # on darwin
    if platform == 'Darwin':
        # assume macports
        systemdir = '/opt/local'
        systemlibdir = os.path.join(systemdir, 'lib')
        systemincdir = os.path.join(systemdir, 'include')

        # set up {python}
        pythonVersion = '3.5'
        pythonMemoryModel = 'm'
        python = 'python' + pythonVersion

        pythondir = os.path.join(
            systemdir, 'Library/Frameworks/Python.framework/Versions', pythonVersion)
        pythonlibdir = os.path.join(pythondir, 'lib')
        pythonincdir = os.path.join(pythondir, 'include', python+pythonMemoryModel)

        # set up the environment
        builder.requirements['python'].environ = {
            'PYTHON': python,
            'PYTHON_LIB': python,
            'PYTHON_PYCFLAGS': '-b',
            'PYTHON_DIR': pythondir,
            'PYTHON_LIBDIR': pythonlibdir,
            'PYTHON_INCDIR': pythonincdir,
            }
        # all done
        return builder

    # on linux
    if platform == 'Linux':
        # assume the canonical layout
        systemdir = '/usr'
        systemlibdir = os.path.join(systemdir, 'lib')
        systemincdir = os.path.join(systemdir, 'include')

        # set up {python}
        pythonVersion = '3.5'
        pythonMemoryModel = 'm'
        python = 'python' + pythonVersion

        pythondir = systemdir
        pythonlibdir = os.path.join(pythondir, 'lib')
        pythonincdir = os.path.join(pythondir, 'include', python+pythonMemoryModel)

        builder.requirements['python'].environ = {
            'PYTHON': python,
            'PYTHON_LIB': python + pythonMemoryModel,
            'PYTHON_PYCFLAGS': '-b',
            'PYTHON_DIR': pythondir,
            'PYTHON_LIBDIR': pythonlibdir,
            'PYTHON_INCDIR': pythonincdir,
            }

        return builder

    # in any case
    return builder

# end of file
