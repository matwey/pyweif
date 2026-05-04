from collections.abc import Callable, Iterable
from typing import overload

from . import af as af, df as df, sf as sf


class SpectralResponse:
    @overload
    def __init__(self, filename: str) -> None: ...

    @overload
    def __init__(self, iter: Iterable[str]) -> None: ...

    def normalize(self) -> SpectralResponse: ...

    def normalized(self) -> SpectralResponse: ...

    def stack(self, other: SpectralResponse) -> None: ...

    def stacked(self, other: SpectralResponse) -> SpectralResponse: ...

    def effective_lambda(self) -> float: ...

class WeightFunction:
    r"""
    Scintillation weight function for axially symmetric power spectra.

    Computes the scintillation weight function for axially symmetric power spectra:

    .. math::

         W(z) = 9.69 \cdot 10^{-3} \cdot 32 \pi^3 z^{5/6} \lambda^{-7/6} \int_0^{\infty} du u^{-8/3} S(u) A\left(\frac{D}{\sqrt{\lambda z}} u\right),

    where :math:`S(u)` is a spectral filter, :math:`\lambda` is its equivalent wavelength, and :math:`A(u)` is an aperture filter.

    The library uses consistent units:
    - Altitudes: kilometers (km)
    - Wavelengths: nanometers (nm)
    - Geometric scales: millimeters (mm)

    See Also
    --------
    :external+libweif:cpp:class:`weif::weight_function` : Base class in C++ library.
    :external+libweif:cpp:func:`weif::sf::poly::equiv_lambda` : Compute equivalent wavelength for polychromatic filters.
    :external+libweif:cpp:member:`weif::math::Kolmogorov_Cn2_scale` : Kolmogorov turbulence scaling.
    """

    def __init__(self, spectral_filter: Callable[[float], float], wavelength: float, aperture_filter: Callable[[float], float], aperture_scale: float, size: int) -> None:
        """
        Construct weight function.

        The weight function is precomputed on a grid of `size` nodes using
        numerical integration technique and subsequent interpolation is used
        when the weight_function::operator()() is invoked.

        Parameters
        ----------
        spectral_filter : SpectralFilter
            Spectral filter function (e.g., Mono, Gauss, Poly).
        wavelength : float
            Wavelength in nanometers.
        aperture_filter : ApertureFilter
            Aperture filter function (e.g., Circular, Annular, CrossAnnular, Point, Square).
        aperture_scale : float
            Aperture scale in millimeters.
        size : int
            Number of grid points for precomputation.

        See Also
        --------
        :external+libweif:cpp:func:`weif::weight_function::weight_function` : Base constructor in C++ library.
        """

    def __call__(self, altitude: float) -> float:
        """
        Evaluate scintillation weight function at specific altitude.

        Parameters
        ----------
        altitude : float
            Atmospheric altitude in kilometers.

        Returns
        -------
        float
            Weight value representing thin layer contribution to scintillation.

        See Also
        --------
        :external+libweif:cpp:func:`weif::weight_function::operator()` : Base function in C++ library.
        """

class WeightFunction2d:
    r"""
    Scintillation weight function for non axially symmetric power spectra.

    Computes the scintillation weight function for non axially symmetric power spectra:

    .. math::

         W(z) = 9.69 \cdot 10^{-3} \cdot 16 \pi^2 z^{5/6} \lambda^{-7/6} \int \mathbf{du} u^{-11/3} S(u) A\left(\frac{D}{\sqrt{\lambda z}} \mathbf{u}\right),

    where :math:`S(u)` is a spectral filter, :math:`\lambda` is its equivalent wavelength, and :math:`A(\mathbf{u})` is an aperture filter.

    The library uses consistent units:
    - Altitudes: kilometers (km)
    - Wavelengths: nanometers (nm)
    - Geometric scales: millimeters (mm)

    See Also
    --------
    :external+libweif:cpp:class:`weif::weight_function_2d` : Base class in C++ library.
    :external+libweif:cpp:func:`weif::sf::poly::equiv_lambda` : Compute equivalent wavelength for polychromatic filters.
    :external+libweif:cpp:member:`weif::math::Kolmogorov_Cn2_scale` : Kolmogorov turbulence scaling.
    """

    def __init__(self, spectral_filter: Callable[[float], float], wavelength: float, aperture_filter: Callable[[float, float], float], aperture_scale: float, size: int) -> None:
        """
        Construct 2D weight function.

        The weight function is precomputed on a grid of `size` nodes using
        numerical integration technique and subsequent interpolation is used
        when the weight_function_2d::operator()() is invoked.

        Parameters
        ----------
        spectral_filter : SpectralFilter
            Spectral filter function (e.g., Mono, Gauss, Poly).
        wavelength : float
            Wavelength in nanometers.
        aperture_filter : ApertureFilter2d
            2D aperture filter function (e.g., Circular, Annular, CrossAnnular, Point, Square).
        aperture_scale : float
            Aperture scale in millimeters.
        size : int
            Number of grid points for precomputation.

        See Also
        --------
        :external+libweif:cpp:func:`weif::weight_function_2d::weight_function_2d` : Base constructor in C++ library.
        """

    def __call__(self, altitude: float) -> float:
        """
        Evaluate scintillation weight function at specific altitude.

        Parameters
        ----------
        altitude : float
            Atmospheric altitude in kilometers.

        Returns
        -------
        float
            Weight value representing thin layer contribution to scintillation.

        See Also
        --------
        :external+libweif:cpp:func:`weif::weight_function_2d::operator()` : Base function in C++ library.
        """
