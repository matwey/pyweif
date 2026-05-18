/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <nanobind/nanobind.h>

#include <weif/spectral_response.h>

#include "sf.h"


namespace nb = nanobind;
namespace sf = weif::sf;

constexpr const char* mono_doc = R"(
Monochromatic spectral filter.

The monochromatic spectral filter is defined as:

.. math::

     E(x) = \sin^2(\pi x),

where :math:`x \equiv z f^2 = \frac{u^2}{\lambda}`.

See Also
--------
:external+libweif:cpp:class:`weif::sf::mono` : Base class in C++ library.
)";

constexpr const char* mono_init_doc = R"(
Constructs a monochromatic spectral filter.
)";

constexpr const char* mono_call_doc = R"(
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
)";

constexpr const char* mono_regular_doc = R"(
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
)";

constexpr const char* gauss_doc = R"(
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
)";

constexpr const char* gauss_init_doc = R"(
Construct a Gaussian spectral filter.

Parameters
----------
fwhm : float
    Full width at half maximum :math:`\Lambda` of the Gaussian envelope expressed in relative units.
)";

constexpr const char* gauss_call_doc = R"(
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
)";

constexpr const char* gauss_regular_doc = R"(
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
)";

constexpr const char* poly_doc = R"(
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
)";

constexpr const char* poly_init_doc = R"(
Construct from spectral response.

Parameters
----------
response : SpectralResponse
    Input spectral response.
size : int
    Interpolation grid size.
)";

constexpr const char* poly_init_carrier_doc = R"(
Construct from spectral response with specified carrier wavelength.

Parameters
----------
response : SpectralResponse
    Input spectral response.
size : int
    Interpolation grid size.
carrier : float
    Carrier wavelength.
)";

constexpr const char* poly_call_doc = R"(
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
)";

constexpr const char* poly_regular_doc = R"(
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
)";

constexpr const char* poly_normalize_doc = R"(
Normalizes the filter in-place.

After normalization the internal wavelengths in filter are expressed
in relative units as expected by weight function integrating routines.

Returns
-------
Poly
    Reference to modified object (self).
)";

constexpr const char* poly_normalized_doc = R"(
Creates normalized copy of the filter.

Returns
-------
Poly
    New normalized filter object.
)";

constexpr const char* poly_equiv_lambda_doc = R"(
Returns equivalent wavelength.

Equivalent wavelength is the wavelength of the monochromatic radiation producing the same scintillation as the polychromatic filter.

Reference: Kornilov V., et al. (2021) "Useful relations for the analysis of stellar scintillation at the entrance pupil of a telescope", https://doi.org/10.1364/JOSAA.420572

Returns
-------
float
    Equivalent wavelength.
)";

constexpr const char* poly_carrier_doc = R"(
Returns carrier wavelength.

Returns
-------
float
    Carrier wavelength.
)";

template<class F> struct get_call_helper;
template<class T, class... Args> struct get_call_helper<T(Args...)> {
	static constexpr auto get_call() noexcept {
		using R = decltype(std::declval<T>()(std::declval<Args>()...));

		return static_cast<R (T::*) (Args...) const>(&T::operator());
	};

	static constexpr auto get_regular() noexcept {
		using R = decltype(std::declval<T>()(std::declval<Args>()...));

		return static_cast<R (T::*) (Args...) const>(&T::regular);
	}
};

template<class F>
constexpr auto get_call() noexcept {
	return get_call_helper<F>::get_call();
}

template<class F>
constexpr auto get_regular() noexcept {
	return get_call_helper<F>::get_regular();
}


void init_sf(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	/* Note, that py::overload_cast<> cannot be used here due to
	 * https://github.com/pybind/pybind11/issues/1153
	 */

	using mono_type = sf::mono<value_type>;
	nb::class_<mono_type>(m, "Mono", mono_doc)
		.def(nb::init<>(), mono_init_doc)
		.def("__call__", get_call<mono_type(value_type)>(), nb::arg("x"), mono_call_doc)
		.def("regular", get_regular<mono_type(value_type)>(), nb::arg("x"), mono_regular_doc);

	using gauss_type = sf::gauss<value_type>;
	nb::class_<gauss_type>(m, "Gauss", gauss_doc)
		.def(nb::init<value_type>(), nb::arg("fwhm"), gauss_init_doc)
		.def("__call__", get_call<gauss_type(value_type)>(), nb::arg("x"), gauss_call_doc)
		.def("regular", get_regular<gauss_type(value_type)>(), nb::arg("x"), gauss_regular_doc);

	using spectral_response_type = weif::spectral_response<value_type>;
	using poly_type = sf::poly<value_type>;
	nb::class_<poly_type>(m, "Poly", poly_doc)
		.def(nb::init<const spectral_response_type&, std::size_t>(), nb::arg("response"), nb::arg("size"), poly_init_doc)
		.def(nb::init<const spectral_response_type&, std::size_t, value_type>(), nb::arg("response"), nb::arg("size"), nb::arg("carrier"), poly_init_carrier_doc)
		.def("__call__", get_call<poly_type(value_type)>(), nb::arg("x"), poly_call_doc)
		.def("regular", get_regular<poly_type(value_type)>(), nb::arg("x"), poly_regular_doc)
		.def("normalize", &poly_type::normalize, poly_normalize_doc)
		.def("normalized", &poly_type::normalized, poly_normalized_doc)
		.def("equiv_lambda", &poly_type::equiv_lambda, poly_equiv_lambda_doc)
		.def("carrier", &poly_type::carrier, poly_carrier_doc);
}
