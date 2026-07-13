from collections.abc import Callable, Iterable
from typing import overload

import numpy
from numpy.typing import NDArray

from . import af as af, df as df, sf as sf


class SpectralResponse:
    """
    Spectral response curve.

    Represents a spectral response curve on a uniform wavelength grid,
    providing operations for normalization, stacking, and analysis.
    The spectral response is typically used as input for polychromatic
    filter calculations.

    See Also
    --------
    :external+libweif:cpp:class:`weif::spectral_response` : Base class in C++ library.
    :external+libweif:cpp:class:`weif::sf::poly` : Polychromatic spectral filter.
    """

    @overload
    def __init__(self, filename: str) -> None:
        """
        Construct spectral response from a file.

        Loads wavelength and response values from a space‑separated text file.

        Parameters
        ----------
        filename : str
            Path to the data file.

        File Format Requirements
        -----------------------
        - Space‑separated values (no multiple spaces are allowed as delimiter)
        - No header row
        - First column: Wavelength values (in nanometers, increasing order)
        - Second column: Corresponding spectral response values

        Example valid file content::

            400.0 0.15
            410.0 0.25
            ...
            700.0 0.05

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::make_from_file` : Base function in C++ library.
        """

    @overload
    def __init__(self, iter: Iterable[str]) -> None:
        """
        Construct spectral response by stacking multiple files.

        Creates a spectral response by loading and stacking (multiplying)
        several response curves from a sequence of filenames.

        Parameters
        ----------
        iter : Iterable[str]
            Iterable of file paths. Each file must satisfy the format
            described in the single‑file constructor.

        The stacking is performed sequentially: the first file defines the
        initial response, and each subsequent file is multiplied (stacked)
        with the accumulated result.

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::stack_from_files` : Base function in C++ library.
        """

    @overload
    def __init__(self, data: NDArray[numpy.float64], *, origin: float, delta: float) -> None: ...

    def normalize(self) -> SpectralResponse:
        r"""
        Normalizes the spectral response in‑place.

        Scales the data so that the total response equals 1:

        .. math::

             \sum_i F(\lambda_i) = 1.

        Returns
        -------
        SpectralResponse
            Reference to the modified object (enables method chaining).

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::normalize` : Base method in C++ library.
        """

    def normalized(self) -> SpectralResponse:
        """
        Creates a normalized copy of the response.

        Returns a new spectral response instance that is normalized
        (see :meth:`normalize`). The original object remains unchanged.

        Returns
        -------
        SpectralResponse
            New normalized spectral response.

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::normalized` : Base method in C++ library.
        """

    def stack(self, other: SpectralResponse) -> None:
        """
        Performs in‑place spectral response stacking (multiplication).

        Multiplies the current response with another spectral response,
        keeping only the wavelength range common to both curves.

        Parameters
        ----------
        other : SpectralResponse
            Another spectral response to stack with current.

        Both spectral responses must have compatible wavelength grids:
        sufficient overlapping wavelength range and identical spacing.

        Raises
        ------
        RuntimeError
            If the grids have no overlapping wavelength range.

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::stack` : Base method in C++ library.
        """

    def stacked(self, other: SpectralResponse) -> SpectralResponse:
        """
        Creates a stacked response (element‑wise multiplication).

        Returns a new spectral response that is the result of stacking
        the current response with another one (see :meth:`stack`).

        Parameters
        ----------
        other : SpectralResponse
            Response to stack with current.

        Returns
        -------
        SpectralResponse
            New stacked spectral response.

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::stacked` : Base method in C++ library.
        """

    def effective_lambda(self) -> float:
        r"""
        Computes the effective wavelength.

        Uses the usual astronomical definition of the effective wavelength:

        .. math::

             \lambda_{\mathrm{eff}} = \frac{\int \lambda R(\lambda) d\lambda}{\int R(\lambda) d\lambda}.

        Returns
        -------
        float
            Effective wavelength in nanometers.

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::effective_lambda` : Base function in C++ library.
        """

    def grid(self) -> NDArray[numpy.float64]: ...

    def data(self) -> NDArray[numpy.float64]:
        """
        Returns the spectral response curve data.

        The data is a 1‑D array of response values corresponding to the wavelength grid.

        Returns
        -------
        ndarray
            One‑dimensional array of response values (same length as the wavelength grid).

        See Also
        --------
        :external+libweif:cpp:func:`weif::spectral_response::data` : Base method in C++ library.
        """

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

    @overload
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

    @overload
    def __call__(self, altitude: NDArray[numpy.float32]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float128]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float32]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float128]) -> NDArray[numpy.float64]: ...

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

    @overload
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

    @overload
    def __call__(self, altitude: NDArray[numpy.float32]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float128]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float32]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, altitude: NDArray[numpy.float128]) -> NDArray[numpy.float64]: ...
