.. _howto:

How-to guides
=============

Installation
------------

Install from PyPI
~~~~~~~~~~~~~~~~~

The easiest way to install pyweif is via pip::

    pip install pyweif

Pre‑built wheels are available for many Python versions and Linux platforms.
The wheels already include the required C++ dependencies, so you do not need to install any required dependencies separately.

Build from sources
~~~~~~~~~~~~~~~~~~

If you need to build pyweif from source (for development purposes or to target a platform for which no wheel is provided),
you can install directly from the repository::

    pip install .

The build requires the following dependencies:

- A C++20 compiler (GCC 10+, Clang 10+, or MSVC)
- `CMake <https://cmake.org/>`_
- `Boost.compat <https://www.boost.org/>`_ library
- Python development headers
- The :external+libweif:doc:`libweif <index>` C++ library

The simplest way to satisfy the ``libweif`` dependency is to use `vcpkg <https://vcpkg.io>`_.
The repository contains a ``vcpkg.json`` manifest that declares the required ports::

    {
      "dependencies": [
        "boost-compat",
        "libweif"
      ]
    }

If you have vcpkg installed and configured (e.g., via ``CMAKE_TOOLCHAIN_FILE``), the build will automatically fetch and build ``libweif`` and its dependencies.
Alternatively, you can install ``libweif`` system‑wide or in any other path if ``PKG_CONFIG_PATH`` is set accordingly.

Once the dependencies are available, the package can be built with::

    pip install .

or, for an editable installation::

    pip install -e .

Contributing
------------

You are welcome to report issues on the `GitHub Issues page <https://github.com/matwey/pyweif/issues>`_.
Pull requests are also accepted on GitHub.

Development dependencies can be installed via the ``dev`` extra::

    pip install -e .[dev]

The project uses `tox <https://tox.readthedocs.io/en/latest/>`_ and `pytest <https://pytest.org/>`_ to run unit tests.