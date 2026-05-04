"""Spectral filter submodule"""

from typing import overload

import pyweif


class Mono:
    r"""
    Monochromatic spectral filter.

    The monochromatic spectral filter is defined as:

    .. math::

         E(x) = \sin^2(\pi x),

    where :math:`x \equiv z f^2 = \frac{u^2}{\lambda}`.

    See Also
    --------
    :external+libweif:cpp:class:`weif::sf::mono` : Base class in C++ library.
    """

    def __init__(self) -> None:
        """Constructs a monochromatic spectral filter."""

    def __call__(self, x: float) -> float:
        r"""
        Call operator for monochromatic spectral filter.

        Evaluates the filter function for a given argument:

        .. math::

             E(x) = \sin^2(\pi x).

        Parameters
        ----------
        x : float
            Normalized squared frequency :math:`x = z f^2 = \frac{u^2}{\lambda}`.

        Returns
        -------
        float
            Filter value at x.

        See Also
        --------
        :external+libweif:cpp:func:`weif::sf::mono::operator()` : Base function in C++ library.
        """

    def regular(self, x: float) -> float:
        r"""
        Evaluate regularized monochromatic spectral filter.

        Evaluates :math:`x^2 E(x)`.

        Parameters
        ----------
        x : float
            Normalized squared frequency :math:`x = z f^2 = \frac{u^2}{\lambda}`.

        Returns
        -------
        float
            Regularized filter value at x.

        See Also
        --------
        :external+libweif:cpp:func:`weif::sf::mono::regular` : Base function in C++ library.
        """

class Gauss:
    r"""
    Gaussian spectral filter.

    The filter combines monochromatic oscillations with Gaussian damping:

    .. math::

         E(x) = \sin^2(\pi x) \cdot \exp\left(-\frac{\pi^2}{8\ln 2} (x \Lambda)^2\right),

    where:
    - :math:`x \equiv z f^2 = \frac{u^2}{\lambda}`,
    - :math:`\Lambda` is the full width at half maximum of the Gaussian envelope expressed in relative units.

    Reference: Tokovinin (2003) "Polychromatic scintillation", https://doi.org/10.1364/JOSAA.20.000686

    See Also
    --------
    :external+libweif:cpp:class:`weif::sf::gauss` : Base class in C++ library.
    """

    def __init__(self, fwhm: float) -> None:
        r"""
        Construct a Gaussian spectral filter.

        Parameters
        ----------
        fwhm : float
            Full width at half maximum :math:`\Lambda` of the Gaussian envelope expressed in relative units.
        """

    def __call__(self, x: float) -> float:
        r"""
        Call operator for Gaussian spectral filter.

        Evaluates the filter function for a given argument:

        .. math::

             E(x) = \sin^2(\pi x) \cdot \exp\left(-\frac{\pi^2}{8\ln 2} (x \Lambda)^2\right).

        Parameters
        ----------
        x : float
            Normalized squared frequency :math:`x = z f^2 = \frac{u^2}{\lambda}`.

        Returns
        -------
        float
            Filter value at x.

        See Also
        --------
        :external+libweif:cpp:func:`weif::sf::gauss::operator()` : Base function in C++ library.
        """

    def regular(self, x: float) -> float:
        r"""
        Evaluate regularized Gaussian spectral filter.

        Evaluates :math:`x^2 E(x)`.

        Parameters
        ----------
        x : float
            Normalized squared frequency :math:`x = z f^2 = \frac{u^2}{\lambda}`.

        Returns
        -------
        float
            Regularized filter value at x.

        See Also
        --------
        :external+libweif:cpp:func:`weif::sf::gauss::regular` : Base function in C++ library.
        """

class Poly:
    """
    Polychromatic spectral filter.

    Evaluates a polychromatic spectral filter using numerically provided spectral response data.
    During construction, the class computes and stores the Fourier transform of the spectral response
    for subsequent evaluations. Internally, it applies the Fourier shift theorem
    by using the carrier wavelength as the new origin point for the spectral
    response, ensuring smooth Fourier transform results and improved numerical
    accuracy. The equivalent wavelength is also evaluated during this process.


    Notes
    -----
    Before using the filter, it must be normalized. Example usage:

    .. code-block:: python

        spectral_filter = Poly(response, 4096)
        equiv_lambda = spectral_filter.equiv_lambda()  # store the wavelength value for later use
        spectral_filter.normalize()  # spectral_filter is now ready for use

    Reference: Tokovinin (2003) "Polychromatic scintillation", https://doi.org/10.1364/JOSAA.20.000686

    See Also
    --------
    :external+libweif:cpp:class:`weif::sf::poly` : Base class in C++ library.
    """

    @overload
    def __init__(self, response: pyweif.SpectralResponse, size: int) -> None:
        """
        Construct from spectral response.

        Parameters
        ----------
        response : SpectralResponse
            Input spectral response.
        size : int
            Interpolation grid size.
        """

    @overload
    def __init__(self, response: pyweif.SpectralResponse, size: int, carrier: float) -> None:
        """
        Construct from spectral response with specified carrier wavelength.

        Parameters
        ----------
        response : SpectralResponse
            Input spectral response.
        size : int
            Interpolation grid size.
        carrier : float
            Carrier wavelength.
        """

    def __call__(self, x: float) -> float:
        r"""
        Call operator for polychromatic spectral filter.

        Evaluates the filter function for a given argument.

        Parameters
        ----------
        x : float
            Normalized squared frequency :math:`x = z f^2 = \frac{u^2}{\lambda}`.

        Returns
        -------
        float
            Filter value at x.

        See Also
        --------
        :external+libweif:cpp:func:`weif::sf::poly::operator()` : Base function in C++ library.
        """

    def regular(self, x: float) -> float:
        r"""
        Evaluate regularized polychromatic spectral filter.

        Evaluates :math:`x^2 E(x)`.

        Parameters
        ----------
        x : float
            Normalized squared frequency :math:`x = z f^2 = \frac{u^2}{\lambda}`.

        Returns
        -------
        float
            Regularized filter value at x.

        See Also
        --------
        :external+libweif:cpp:func:`weif::sf::poly::regular` : Base function in C++ library.
        """

    def normalize(self) -> Poly:
        """
        Normalizes the filter in-place.

        After normalization the internal wavelengths in filter are expressed
        in relative units as expected by weight function integrating routines.

        Returns
        -------
        Poly
            Reference to modified object (self).
        """

    def normalized(self) -> Poly:
        """
        Creates normalized copy of the filter.

        Returns
        -------
        Poly
            New normalized filter object.
        """

    def equiv_lambda(self) -> float:
        """
        Returns equivalent wavelength.

        Equivalent wavelength is the wavelength of the monochromatic radiation producing the same scintillation as the polychromatic filter.

        Reference: Kornilov V., et al. (2021) "Useful relations for the analysis of stellar scintillation at the entrance pupil of a telescope", https://doi.org/10.1364/JOSAA.420572

        Returns
        -------
        float
            Equivalent wavelength.
        """

    def carrier(self) -> float:
        """
        Returns carrier wavelength.

        Returns
        -------
        float
            Carrier wavelength.
        """
