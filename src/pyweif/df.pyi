"""Digital filter submodule"""

from collections.abc import Callable, Sequence
from typing import overload

import numpy
from numpy.typing import NDArray


class DigitalFilter2d:
    r"""
    Digital filter function.

    Implements a two‑dimensional digital filter defined by its impulse response.
    The filter can be constructed either from a function :math:`\Omega(u_x, u_y)` evaluated on
    a frequency grid, or directly from an impulse response tensor.

    The digital filter function :math:`\Omega(u_x, u_y)` is evaluated on an appropriate frequency
    grid spanning :math:`[0, 0.5] \times [0, 0.5]` in dimensionless frequency space, and the
    filter impulse response is calculated using Fast Fourier Transform.

    See Also
    --------
    :external+libweif:cpp:class:`weif::digital_filter_2d` : Base class in C++ library.
    """

    @overload
    def __init__(self, fun: Callable[[float, float], float], shape: Sequence[int]) -> None:
        r"""
        Construct digital filter from a function.

        Parameters
        ----------
        fun : Callable[[float, float], float]
            Digital filter function :math:`\Omega(u_x, u_y)` that returns the filter response
            for given dimensionless frequency coordinates.
        shape : tuple[int, int]
            Filter dimensions (Nx, Ny). The impulse response will be computed
            on a grid of this size.

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::digital_filter_2d` : Base constructor in C++ library.
        """

    @overload
    def __init__(self, impulse_response: NDArray[numpy.float32]) -> None:
        """
        Construct digital filter directly from impulse response tensor.

        Parameters
        ----------
        impulse_response : ndarray
            2‑D array containing the filter impulse response values.
            The shape of the array determines the filter dimensions (Nx, Ny).

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::digital_filter_2d` : Base constructor in C++ library.
        """

    @overload
    def __init__(self, impulse_response: NDArray[numpy.float64]) -> None:
        """
        Construct digital filter directly from impulse response tensor.

        Parameters
        ----------
        impulse_response : ndarray
            2‑D array containing the filter impulse response values.
            The shape of the array determines the filter dimensions (Nx, Ny).

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::digital_filter_2d` : Base constructor in C++ library.
        """

    @overload
    def __init__(self, impulse_response: NDArray[numpy.float128]) -> None:
        """
        Construct digital filter directly from impulse response tensor.

        Parameters
        ----------
        impulse_response : ndarray
            2‑D array containing the filter impulse response values.
            The shape of the array determines the filter dimensions (Nx, Ny).

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::digital_filter_2d` : Base constructor in C++ library.
        """

    def mix(self) -> DigitalFilter2d:
        """
        Performs in‑place amplitude mixing.

        Modifies the impulse response by subtracting a checkerboard sign‑alternation
        pattern to set the center (0,0) to zero. This operation is used to remove
        the DC component of the filter.

        Returns
        -------
        DigitalFilter2d
            Reference to the modified filter (enables method chaining).

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::mix` : Base method in C++ library.
        """

    def mixed(self) -> DigitalFilter2d:
        """
        Creates a mixed version of the filter.

        Returns a new filter instance that is the result of applying the mixing
        operation (see :meth:`mix`). The original filter remains unchanged.

        Returns
        -------
        DigitalFilter2d
            New mixed filter instance.

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::mixed` : Base method in C++ library.
        """

    @overload
    def __call__(self, ux: float, uy: float) -> float:
        """
        Evaluate digital filter at specific frequency coordinates.

        Computes the filter response for given dimensionless frequency components
        using the discrete Fourier transform of the impulse response.

        Parameters
        ----------
        ux : float
            Dimensionless frequency x‑component.
        uy : float
            Dimensionless frequency y‑component.

        Returns
        -------
        float
            Filter response value.

        See Also
        --------
        :external+libweif:cpp:func:`weif::digital_filter_2d::operator()` : Base function in C++ library.
        """

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float32], uy: NDArray[numpy.float32]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float64], uy: NDArray[numpy.float64]) -> NDArray[numpy.float64]: ...

    @overload
    def __call__(self, ux: NDArray[numpy.float128], uy: NDArray[numpy.float128]) -> NDArray[numpy.float64]: ...
