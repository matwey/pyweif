/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <xtensor.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/typing.h>

#include <weif/spectral_response.h>


namespace nb = nanobind;


void init_spectral_response(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	using spectral_response_type = weif::spectral_response<value_type>;
	nb::class_<spectral_response_type>(m, "SpectralResponse")
//		.def(nb::init(&spectral_response_type::make_from_file))
		.def("normalize", &spectral_response_type::normalize)
		.def("normalized", &spectral_response_type::normalized)
		.def("stack", &spectral_response_type::stack)
		.def("stacked", &spectral_response_type::stacked)
		.def("effective_lambda", &spectral_response_type::effective_lambda)
		.def("data", &spectral_response_type::data);
}
