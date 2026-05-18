/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <nanobind/nanobind.h>
#include <nanobind/xtensor.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/function.h>

#include <weif/digital_filter_2d.h>


namespace nb = nanobind;


constexpr const char* digital_filter_2d_doc = R"(
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
)";

constexpr const char* digital_filter_2d_init_doc = R"(
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
)";

constexpr const char* digital_filter_2d_init_tensor_doc = R"(
Construct digital filter directly from impulse response tensor.

Parameters
----------
impulse_response : ndarray
    2‑D array containing the filter impulse response values.
    The shape of the array determines the filter dimensions (Nx, Ny).

See Also
--------
:external+libweif:cpp:func:`weif::digital_filter_2d::digital_filter_2d` : Base constructor in C++ library.
)";

constexpr const char* digital_filter_2d_mix_doc = R"(
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
)";

constexpr const char* digital_filter_2d_mixed_doc = R"(
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
)";

constexpr const char* digital_filter_2d_call_doc = R"(
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
)";


template<class F> struct get_call_helper;
template<class T, class... Args> struct get_call_helper<T(Args...)> {
	static constexpr auto get_call() noexcept {
		using R = decltype(std::declval<T>()(std::declval<Args>()...));

		return static_cast<R (T::*) (Args...) const>(&T::operator());
	};
};

template<class F>
constexpr auto get_call() noexcept {
	return get_call_helper<F>::get_call();
}


void init_df(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	/* Note, that py::overload_cast<> cannot be used here due to
	 * https://github.com/pybind/pybind11/issues/1153
	 */

	using digital_filter_2d_type = weif::digital_filter_2d<value_type>;
	nb::class_<digital_filter_2d_type>(m, "DigitalFilter2d", digital_filter_2d_doc)
		.def(nb::init<std::function<value_type(value_type, value_type)>, digital_filter_2d_type::shape_type>(), nb::arg("fun"), nb::arg("shape"), digital_filter_2d_init_doc)
		.def(nb::init<const nb::xtensor_view<float, 2>&>(), nb::arg("impulse_response"), digital_filter_2d_init_tensor_doc)
		.def(nb::init<const nb::xtensor_view<double, 2>&>(), nb::arg("impulse_response"), digital_filter_2d_init_tensor_doc)
		.def(nb::init<const nb::xtensor_view<long double, 2>&>(), nb::arg("impulse_response"), digital_filter_2d_init_tensor_doc)
		.def("mix", &digital_filter_2d_type::mix, digital_filter_2d_mix_doc)
		.def("mixed", &digital_filter_2d_type::mixed, digital_filter_2d_mixed_doc)
		.def("__call__", get_call<digital_filter_2d_type(value_type, value_type)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc)
		.def("__call__", get_call<digital_filter_2d_type(const nb::xarray_view<float>&, const nb::xarray_view<float>&)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc)
		.def("__call__", get_call<digital_filter_2d_type(const nb::xarray_view<double>&, const nb::xarray_view<double>&)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc)
		.def("__call__", get_call<digital_filter_2d_type(const nb::xarray_view<long double>&, const nb::xarray_view<long double>&)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc)
		.def("__call__", get_call<digital_filter_2d_type(const nb::xtensor_view<float, 1>&, const nb::xtensor_view<float, 1>&)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc)
		.def("__call__", get_call<digital_filter_2d_type(const nb::xtensor_view<double, 1>&, const nb::xtensor_view<double, 1>&)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc)
		.def("__call__", get_call<digital_filter_2d_type(const nb::xtensor_view<long double, 1>&, const nb::xtensor_view<long double, 1>&)>(), nb::arg("ux"), nb::arg("uy"), digital_filter_2d_call_doc);
}

