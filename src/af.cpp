/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <nanobind/nanobind.h>

#include "af.h"


namespace nb = nanobind;
namespace af = weif::af;


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


void init_af(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	/* Note, that py::overload_cast<> cannot be used here due to
	 * https://github.com/pybind/pybind11/issues/1153
	 */

	using circular_type = af::circular<value_type>;
	nb::class_<circular_type>(m, "Circular")
		.def(nb::init<>())
		.def("__call__", get_call<value_type, circular_type(value_type)>())
		.def("__call__", get_call<value_type, circular_type(value_type, value_type)>());

	using annular_type = af::annular<value_type>;
	nb::class_<af::annular<value_type>>(m, "Annular")
		.def(nb::init<value_type>())
		.def("__call__", get_call<value_type, annular_type(value_type)>())
		.def("__call__", get_call<value_type, annular_type(value_type, value_type)>());

	using cross_annular_type = af::cross_annular<value_type>;
	nb::class_<af::cross_annular<value_type>>(m, "CrossAnnular")
		.def(nb::init<value_type, value_type, value_type>())
		.def("__call__", get_call<value_type, cross_annular_type(value_type)>())
		.def("__call__", get_call<value_type, cross_annular_type(value_type, value_type)>());

	using point_type = af::point<value_type>;
	nb::class_<point_type>(m, "Point")
		.def(nb::init<>())
		.def("__call__", get_call<value_type, point_type(value_type)>())
		.def("__call__", get_call<value_type, point_type(value_type, value_type)>());

	using square_type = af::square<value_type>;
	nb::class_<square_type>(m, "Square")
		.def(nb::init<>())
		.def("__call__", get_call<value_type, square_type(value_type, value_type)>());
}
