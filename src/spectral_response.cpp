/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <ranges>

#include <nanobind/nanobind.h>
#include <nanobind/typing.h>
#include <nanobind/stl/string.h>

#include <weif/spectral_response.h>


namespace nb = nanobind;


constexpr const char* spectral_response_doc = R"(
Spectral response curve.

Represents a spectral response curve on a uniform wavelength grid,
providing operations for normalization, stacking, and analysis.
The spectral response is typically used as input for polychromatic
filter calculations.

See Also
--------
:external+libweif:cpp:class:`weif::spectral_response` : Base class in C++ library.
:external+libweif:cpp:class:`weif::sf::poly` : Polychromatic spectral filter.
)";

constexpr const char* spectral_response_init_file_doc = R"(
Construct spectral response from a file.

Loads wavelength and response values from a space‑separated text file.

Parameters
----------
filename : str
    Path to the data file.

File Format Requirements
-----------------------
- Space‑separated values (no multiple spaces are allowed as delimiter)
- No header row
- First column: Wavelength values (in nanometers, increasing order)
- Second column: Corresponding spectral response values

Example valid file content::

    400.0 0.15
    410.0 0.25
    ...
    700.0 0.05

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::make_from_file` : Base function in C++ library.
)";

constexpr const char* spectral_response_init_iter_doc = R"(
Construct spectral response by stacking multiple files.

Creates a spectral response by loading and stacking (multiplying)
several response curves from a sequence of filenames.

Parameters
----------
iter : Iterable[str]
    Iterable of file paths. Each file must satisfy the format
    described in the single‑file constructor.

The stacking is performed sequentially: the first file defines the
initial response, and each subsequent file is multiplied (stacked)
with the accumulated result.

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::stack_from_files` : Base function in C++ library.
)";

constexpr const char* spectral_response_normalize_doc = R"(
Normalizes the spectral response in‑place.

Scales the data so that the total response equals 1:

.. math::

     \sum_i F(\lambda_i) = 1.

Returns
-------
SpectralResponse
    Reference to the modified object (enables method chaining).

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::normalize` : Base method in C++ library.
)";

constexpr const char* spectral_response_normalized_doc = R"(
Creates a normalized copy of the response.

Returns a new spectral response instance that is normalized
(see :meth:`normalize`). The original object remains unchanged.

Returns
-------
SpectralResponse
    New normalized spectral response.

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::normalized` : Base method in C++ library.
)";

constexpr const char* spectral_response_stack_doc = R"(
Performs in‑place spectral response stacking (multiplication).

Multiplies the current response with another spectral response,
keeping only the wavelength range common to both curves.

Parameters
----------
other : SpectralResponse
    Another spectral response to stack with current.

Both spectral responses must have compatible wavelength grids:
sufficient overlapping wavelength range and identical spacing.

Raises
------
RuntimeError
    If the grids have no overlapping wavelength range.

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::stack` : Base method in C++ library.
)";

constexpr const char* spectral_response_stacked_doc = R"(
Creates a stacked response (element‑wise multiplication).

Returns a new spectral response that is the result of stacking
the current response with another one (see :meth:`stack`).

Parameters
----------
other : SpectralResponse
    Response to stack with current.

Returns
-------
SpectralResponse
    New stacked spectral response.

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::stacked` : Base method in C++ library.
)";

constexpr const char* spectral_response_effective_lambda_doc = R"(
Computes the effective wavelength.

Uses the usual astronomical definition of the effective wavelength:

.. math::

     \lambda_{\mathrm{eff}} = \frac{\int \lambda R(\lambda) d\lambda}{\int R(\lambda) d\lambda}.

Returns
-------
float
    Effective wavelength in nanometers.

See Also
--------
:external+libweif:cpp:func:`weif::spectral_response::effective_lambda` : Base function in C++ library.
)";


void init_spectral_response(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	using spectral_response_type = weif::spectral_response<value_type>;
	nb::class_<spectral_response_type>(m, "SpectralResponse", spectral_response_doc)
		.def("__init__", [] (spectral_response_type* s, const std::string& filename) {
			new (s) spectral_response_type{spectral_response_type::make_from_file(filename)};
		}, nb::arg("filename"), spectral_response_init_file_doc)
		.def("__init__", [] (spectral_response_type* s, nb::typed<nb::iterable, std::string> iter) {
			const auto filenames = std::ranges::transform_view(iter,
				[] (nb::handle h) { return nb::cast<std::string>(h); });

			new (s) spectral_response_type{spectral_response_type::stack_from_files(std::cbegin(filenames), std::cend(filenames))};
		}, nb::arg("iter"), spectral_response_init_iter_doc)
		.def("normalize", &spectral_response_type::normalize, spectral_response_normalize_doc)
		.def("normalized", &spectral_response_type::normalized, spectral_response_normalized_doc)
		.def("stack", &spectral_response_type::stack, nb::arg("other"), spectral_response_stack_doc)
		.def("stacked", &spectral_response_type::stacked, nb::arg("other"), spectral_response_stacked_doc)
		.def("effective_lambda", &spectral_response_type::effective_lambda, spectral_response_effective_lambda_doc);
}
