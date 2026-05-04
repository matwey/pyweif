/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <nanobind/nanobind.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/variant.h>

#include <weif/weight_function.h>
#include <weif/weight_function_2d.h>
#include <weif/weight_function_grid_2d.h>

#include "af.h"
#include "sf.h"


namespace nb = nanobind;


constexpr const char* weight_function_doc = R"(
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
)";

constexpr const char* weight_function_init_doc = R"(
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
)";

constexpr const char* weight_function_call_doc = R"(
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
)";

constexpr const char* weight_function_2d_doc = R"(
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
)";

constexpr const char* weight_function_2d_init_doc = R"(
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
)";

constexpr const char* weight_function_2d_call_doc = R"(
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
)";


template<class F> struct get_call_helper;
template<class T, class... Args> struct get_call_helper<T(Args...)> {
	static constexpr auto get_call() noexcept {
		using R = decltype(std::declval<T>()(std::declval<Args>()...));

		return static_cast<R (T::*) (Args...) const>(&T::operator());
	};
};

template<class, class F>
constexpr auto get_call() noexcept {
	return get_call_helper<F>::get_call();
}


void init_weight_function(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	using weight_function_type = weif::weight_function<value_type>;
	nb::class_<weight_function_type>(m, "WeightFunction", weight_function_doc)
		.def(nb::init<py_sf<value_type>, value_type, py_af<value_type>, value_type, std::size_t>(),
			nb::arg("spectral_filter"), nb::arg("wavelength"), nb::arg("aperture_filter"), nb::arg("aperture_scale"), nb::arg("size"),
			weight_function_init_doc)
		.def("__call__", get_call<value_type, weight_function_type(value_type)>(), nb::arg("altitude"), weight_function_call_doc);

	using weight_function_2d_type = weif::weight_function_2d<value_type>;
	nb::class_<weight_function_2d_type>(m, "WeightFunction2d", weight_function_2d_doc)
		.def(nb::init<py_sf<value_type>, value_type, py_af_2d<value_type>, value_type, std::size_t>(),
			nb::arg("spectral_filter"), nb::arg("wavelength"), nb::arg("aperture_filter"), nb::arg("aperture_scale"), nb::arg("size"),
			weight_function_2d_init_doc)
		.def("__call__", get_call<value_type, weight_function_2d_type(value_type)>(), nb::arg("altitude"), weight_function_2d_call_doc);

#if 0
	using weight_function_grid_2d_type = weif::weight_function_grid_2d<value_type>;
	nb::class_<weight_function_grid_2d_type>(m, "WeightFunctionGrid2d")
//		.def(nb::init<py_spectral_filter, value_type, py_aperture_filter, value_type, weight_function_grid_2d_type::shape_type>());
#endif

}
