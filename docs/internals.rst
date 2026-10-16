.. _internals:

Internals
=========

This page describes internal design decisions, conventions, and policies used
in the `pyweif` library.

Versioning
----------

`pyweif` follows the `Semantic Versioning <https://semver.org/>`_ (SemVer)
scheme of the underlying `libweif <https://libweif.readthedocs.io/en/latest/>`_
C++ library. The version number is expressed as **MAJOR.MINOR.PATCH**:

- **MAJOR** version increments indicate incompatible API changes.
- **MINOR** version increments add functionality in a backward-compatible manner.
- **PATCH** version increments are for backward-compatible bug fixes.

Under normal circumstances, ``pyweif`` is supposed to be SemVer compatible
with ``libweif``: the Python API mirrors the C++ one, so an incompatible
change in ``libweif`` implies an incompatible change in ``pyweif``, and a new
feature of ``libweif`` is exposed as a new feature of ``pyweif``.

The exception to this rule is the release policy. For every ``libweif``
**X.Y.Z** release, a matching ``pyweif`` **X.Y.Z** release is published in
order to provide pre-built wheels (see :ref:`How-to guides <howto>`). Such
releases may carry no functional changes of their own — they exist to ship
binary packages bound to the corresponding ``libweif`` version.

While the major version is zero (0.y.z), the library is considered to be in
initial development. During this phase, the public API may still change in
backward-incompatible ways.

The ``pyweif`` version is defined in ``pyproject.toml`` and propagated to the
CMake build by scikit-build-core. It can be queried at runtime via
``pyweif.__version__``.

Measurement unit conventions
----------------------------

To ensure consistency across all calculations, a fixed set of measurement
units is adopted. All input parameters must be supplied in these units; no
automatic unit conversion is performed.

.. list-table::
   :header-rows: 1

   * - Quantity
     - Unit
     - Notes
   * - Altitude :math:`z`
     - kilometers (km)
     - Turbulence layer heights and propagation distances.
   * - Wavelength :math:`\lambda`
     - nanometers (nm)
     - Optical wavelengths.
   * - Geometric scales :math:`D`
     - millimeters (mm)
     - Aperture diameter, Fresnel radius, and other length scales.

This choice is justified because the parameters are internally combined into
the following dimensionless combination in most cases:

.. math::

     \frac{D}{\sqrt{\lambda z}}.

When the quantities are substituted in the chosen units, the result is
automatically correct.

Note also that the filter frequency arguments are unitless. Aperture filters
take the unitless spatial frequency :math:`u`, and spectral filters take the
normalized squared frequency :math:`x = z f^2 = u^2/\lambda`. Physical scales
are introduced by the caller through the aperture scale and the equivalent
wavelength (see :ref:`How-to guides <howto>`).

Binding technology
------------------

`pyweif` is a `nanobind <https://nanobind.readthedocs.io/>`_-based binding of
the `libweif` C++ library. nanobind is a lightweight C++ binding library
sharing its design with pybind11, offering lower call overheads and smaller
binary sizes.

The vectorized (tensor) interfaces of ``pyweif`` rely on the `xtensor
<https://github.com/xtensor-stack/xtensor>`_ support for nanobind introduced
by Vladimir Cherepanov in `wjakob/nanobind#1328
<https://github.com/wjakob/nanobind/pull/1328>`_.
