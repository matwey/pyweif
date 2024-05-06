/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <xtensor.hpp>
#include <nanobind/nanobind.h>


namespace nb = nanobind;


void init_af(nb::module_&);
void init_sf(nb::module_&);
void init_df(nb::module_&);
void init_spectral_response(nb::module_&);
void init_weight_function(nb::module_&);


NB_MODULE(pyweif, m) {
	m.attr("__version__") = VERSION_INFO;

	auto m_af = m.def_submodule("af", "Aperture filter submodule");
	init_af(m_af);
	auto m_sf = m.def_submodule("sf", "Spectral filter submodule");
	init_sf(m_sf);
	init_spectral_response(m);
	init_weight_function(m);
	auto m_df = m.def_submodule("df", "Digital filter submodule");
	init_df(m_df);
}
