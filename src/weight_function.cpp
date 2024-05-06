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
	nb::class_<weight_function_type>(m, "WeightFunction")
		.def(nb::init<py_sf<value_type>, value_type, py_af<value_type>, value_type, std::size_t>())
		.def("__call__", get_call<value_type, weight_function_type(value_type)>());

	using weight_function_2d_type = weif::weight_function_2d<value_type>;
	nb::class_<weight_function_2d_type>(m, "WeightFunction2d")
		.def(nb::init<py_sf<value_type>, value_type, py_af_2d<value_type>, value_type, std::size_t>())
		.def("__call__", get_call<value_type, weight_function_2d_type(value_type)>());

#if 0
	using weight_function_grid_2d_type = weif::weight_function_grid_2d<value_type>;
	nb::class_<weight_function_grid_2d_type>(m, "WeightFunctionGrid2d")
//		.def(nb::init<py_spectral_filter, value_type, py_aperture_filter, value_type, weight_function_grid_2d_type::shape_type>());
#endif

}
