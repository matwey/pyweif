/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <xtensor.hpp>
#include <nanobind/nanobind.h>

#include <weif/spectral_response.h>

#include "sf.h"


namespace nb = nanobind;
namespace sf = weif::sf;


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

template<class, class F>
constexpr auto get_call() noexcept {
	return get_call_helper<F>::get_call();
}

template<class, class F>
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
	nb::class_<mono_type>(m, "Mono")
		.def(nb::init<>())
		.def("__call__", get_call<value_type, mono_type(value_type)>())
		.def("regular", get_regular<value_type, mono_type(value_type)>());

	using gauss_type = sf::gauss<value_type>;
	nb::class_<gauss_type>(m, "Gauss")
		.def(nb::init<value_type>())
		.def("__call__", get_call<value_type, gauss_type(value_type)>())
		.def("regular", get_regular<value_type, gauss_type(value_type)>());

	using spectral_response_type = weif::spectral_response<value_type>;
	using poly_type = sf::poly<value_type>;
	nb::class_<poly_type>(m, "Poly")
		.def(nb::init<const spectral_response_type&, std::size_t>())
		.def(nb::init<const spectral_response_type&, std::size_t, value_type>())
		.def("__call__", get_call<value_type, poly_type(value_type)>())
		.def("regular", get_regular<value_type, poly_type(value_type)>())
		.def("normalize", &poly_type::normalize)
		.def("normalized", &poly_type::normalized)
		.def("equiv_lambda", &poly_type::equiv_lambda)
		.def("carrier", &poly_type::carrier);
}
