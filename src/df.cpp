/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <nanobind/nanobind.h>

#include <weif/digital_filter_2d.h>


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


void init_df(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	/* Note, that py::overload_cast<> cannot be used here due to
	 * https://github.com/pybind/pybind11/issues/1153
	 */

	using digital_filter_2d_type = weif::digital_filter_2d<value_type>;
	nb::class_<digital_filter_2d_type>(m, "DigitalFilter2d")
		.def(nb::init<std::function<value_type(value_type, value_type)>, digital_filter_2d_type::shape_type>())
		.def("mix", &digital_filter_2d_type::mix)
		.def("mixed", &digital_filter_2d_type::mixed)
		.def("__call__", get_call<value_type, digital_filter_2d_type(value_type, value_type)>());
}

