"""Aperture filter submodule"""

from typing import overload

import numpy
from numpy.typing import NDArray


class Circular:
    r"""
    Aperture filter function for a circular aperture.

    The aperture filter is defined in both radial and Cartesian plane coordinates:

    .. math::

         A(u) &= \mathrm{jinc}_1^2(\pi u),\\
         A(u_x, u_y) &= \mathrm{jinc}_1^2\left(\pi \sqrt{u_x^2 + u_y^2}\right),

    where :math:`\mathrm{jinc}_1(x) = \frac{2 J_1(x)}{x}` is the jinc function
    (Fourier transform of a unit circular aperture) and :math:`J_1` is the
    Bessel function of the first kind.

    See Also
    --------
    :external+libweif:cpp:class:`weif::af::circular` : Base class in C++ library.
    """

    def __init__(self) -> None:
        """Constructs an circular aperture filter."""

    @overload
    def __call__(self, u: float) -> float:
        r"""
        Call operator for circular aperture filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Evaluates the squared jinc function for given radial frequency:

        .. math::

             A(u) = \mathrm{jinc}_1^2(\pi u).

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: float, uy: float) -> float:
        r"""
        Call operator for circular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        r"""
        Call operator for circular aperture filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Evaluates the squared jinc function for given radial frequency:

        .. math::

             A(u) = \mathrm{jinc}_1^2(\pi u).

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        r"""
        Call operator for circular aperture filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Evaluates the squared jinc function for given radial frequency:

        .. math::

             A(u) = \mathrm{jinc}_1^2(\pi u).

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        r"""
        Call operator for circular aperture filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Evaluates the squared jinc function for given radial frequency:

        .. math::

             A(u) = \mathrm{jinc}_1^2(\pi u).

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        r"""
        Call operator for circular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        r"""
        Call operator for circular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        r"""
        Call operator for circular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
        """

class Annular:
    r"""
    Aperture filter function for an annular (ring-shaped) aperture.

    The aperture filter accounts for central obscuration and is defined as:

    .. math::

         A(u) &= \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2},\\
         A(u_x, u_y) &= A\left(\sqrt{u_x^2 + u_y^2}\right),

    where :math:`\epsilon` is the obscuration ratio (:math:`0 \le \epsilon < 1`),
    and :math:`\mathrm{jinc}_1(x) = \frac{2 J_1(x)}{x}` is the jinc function
    (Fourier transform of a unit circular aperture) and :math:`J_1` is the
    Bessel function of the first kind.

    See Also
    --------
    :external+libweif:cpp:class:`weif::af::annular` : Base class in C++ library.
    """

    def __init__(self, obscuration: float) -> None:
        r"""
        Constructs an annular aperture filter with given obscuration.

        Parameters
        ----------
        obscuration : float
            Central obscuration ratio (:math:`0 \le \epsilon < 1`)
        """

    @overload
    def __call__(self, u: float) -> float:
        r"""
        Call operator for annular aperture filter in radial coordinates.

        Evaluates the squared normalized difference of jinc functions:

        .. math::

             A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2}.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: float, uy: float) -> float:
        r"""
        Call operator for annular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        r"""
        Call operator for annular aperture filter in radial coordinates.

        Evaluates the squared normalized difference of jinc functions:

        .. math::

             A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2}.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        r"""
        Call operator for annular aperture filter in radial coordinates.

        Evaluates the squared normalized difference of jinc functions:

        .. math::

             A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2}.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        r"""
        Call operator for annular aperture filter in radial coordinates.

        Evaluates the squared normalized difference of jinc functions:

        .. math::

             A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2}.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        r"""
        Call operator for annular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        r"""
        Call operator for annular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        r"""
        Call operator for annular aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
        """

class CrossAnnular:
    r"""
    Aperture filter for covariance between two concentric annular apertures.

    Models the covariance of relative flux fluctuations between two annular apertures
    as used in MASS (Multi-Aperture Scintillation Sensor) instruments:

    .. math::

         A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon_1^2 \mathrm{jinc}_1(\pi \epsilon_1 u)\right)}{(1 - \epsilon_1^2)}
                \times \frac{\left(\mathrm{jinc}_1(\pi \alpha u) - \epsilon_2^2 \mathrm{jinc}_1(\pi \epsilon_2 \alpha u)\right)}{(1 - \epsilon_2^2)},

    where:
    - :math:`\epsilon_1` is the central obscuration ratio of the first aperture,
    - :math:`\epsilon_2` is the central obscuration ratio of the second aperture,
    - :math:`\alpha = D_2/D_1` is the diameter ratio between apertures.

    Reference: Tokovinin, et. al. (2003) "Restoration of turbulence profile from scintillation indices", https://doi.org/10.1046/j.1365-8711.2003.06731.x

    See Also
    --------
    :external+libweif:cpp:class:`weif::af::cross_annular` : Base class in C++ library.
    """

    def __init__(self, ratio: float, obscuration_first: float, obscuration_second: float) -> None:
        r"""
        Constructs an aperture filter for covariance of two annular apertures.

        Parameters
        ----------
        ratio : float
            Diameter ratio :math:`\alpha = D_2/D_1` between apertures.
        obscuration_first : float
            Obscuration ratio :math:`\epsilon_1` of first aperture (:math:`0 \le \epsilon_1 < 1`).
        obscuration_second : float
            Obscuration ratio :math:`\epsilon_2` of second aperture (:math:`0 \le \epsilon_2 < 1`).
        """

    @overload
    def __call__(self, u: float) -> float:
        """
        Call operator for the aperture filter in radial coordinates.

        Evaluates the filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: float, uy: float) -> float:
        r"""
        Call operator for the aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        """
        Call operator for the aperture filter in radial coordinates.

        Evaluates the filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        """
        Call operator for the aperture filter in radial coordinates.

        Evaluates the filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        """
        Call operator for the aperture filter in radial coordinates.

        Evaluates the filter in radial coordinates.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value at specified frequency

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        r"""
        Call operator for the aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        r"""
        Call operator for the aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        r"""
        Call operator for the aperture filter in Cartesian coordinates.

        Evaluates the filter by converting to radial coordinates:

        .. math::

             A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequency coordinates

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
        """

class Point:
    """
    Aperture filter function for a point (infinitely small) aperture.

    The aperture filter is defined in both radial and Cartesian plane coordinates:

    .. math::

         A(u) = A(u_x, u_y) = 1.

    This represents an ideal point aperture.

    See Also
    --------
    :external+libweif:cpp:class:`weif::af::point` : Base class in C++ library.
    """

    def __init__(self) -> None:
        """Constructs a point aperture filter."""

    @overload
    def __call__(self, u: float) -> float:
        """
        Call operator for point aperture filter in radial coordinates.

        Evaluates the filter function for a given radial frequency:

        .. math::

             A(u) = 1.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: float, uy: float) -> float:
        """
        Call operator for point aperture filter in Cartesian coordinates.

        Evaluates the filter function for given frequency components:

        .. math::

             A(u_x, u_y) = 1.

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        """
        Call operator for point aperture filter in radial coordinates.

        Evaluates the filter function for a given radial frequency:

        .. math::

             A(u) = 1.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        """
        Call operator for point aperture filter in radial coordinates.

        Evaluates the filter function for a given radial frequency:

        .. math::

             A(u) = 1.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, u: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        """
        Call operator for point aperture filter in radial coordinates.

        Evaluates the filter function for a given radial frequency:

        .. math::

             A(u) = 1.

        Parameters
        ----------
        u : float
            Dimensionless spatial frequency magnitude (radial coordinate)

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float32]:
        """
        Call operator for point aperture filter in Cartesian coordinates.

        Evaluates the filter function for given frequency components:

        .. math::

             A(u_x, u_y) = 1.

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]:
        """
        Call operator for point aperture filter in Cartesian coordinates.

        Evaluates the filter function for given frequency components:

        .. math::

             A(u_x, u_y) = 1.

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float128]:
        """
        Call operator for point aperture filter in Cartesian coordinates.

        Evaluates the filter function for given frequency components:

        .. math::

             A(u_x, u_y) = 1.

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency component in x-direction.
        uy : float
            Dimensionless spatial frequency component in y-direction.

        Returns
        -------
        float
            Aperture filter value (always 1 for point aperture)

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
        """

class Square:
    r"""
    Aperture filter function for a square aperture.

    The aperture filter is defined in Cartesian coordinates as:

    .. math::

         A(u_x, u_y) = \mathrm{sinc}^2(\pi u_x) \cdot \mathrm{sinc}^2(\pi u_y),

    representing the Fourier transform of a square pupil function.

    See Also
    --------
    :external+libweif:cpp:class:`weif::af::square` : Base class in C++ library.
    """

    def __init__(self) -> None:
        """Constructs a square aperture filter."""

    @overload
    def __call__(self, ux: float, uy: float) -> float:
        r"""
        Call operator for square aperture filter in Cartesian coordinates.

        Evaluates the squared 2D sinc function:

        .. math::

             A(u_x, u_y) = \mathrm{sinc}^2(\pi u_x) \cdot \mathrm{sinc}^2(\pi u_y).

        Parameters
        ----------
        ux : float
            Dimensionless spatial frequency in x-direction.
        uy : float
            Dimensionless spatial frequency in y-direction.

        Returns
        -------
        float
            Aperture filter value at specified frequencies

        See Also
        --------
        :external+libweif:cpp:func:`weif::af::square::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float32]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float128]: ...
