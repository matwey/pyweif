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


constexpr const char* circular_doc = R"(
Aperture filter function for a circular aperture.

The aperture filter is defined in both radial and Cartesian plane coordinates:

.. math::

     A(u) &= \mathrm{jinc}_1^2(\pi u),\\
     A(u_x, u_y) &= \mathrm{jinc}_1^2\left(\pi \sqrt{u_x^2 + u_y^2}\right),

where :math:`\mathrm{jinc}_1(x) = \frac{2 J_1(x)}{x}` is the jinc function
(Fourier transform of a unit circular aperture) and :math:`J_1` is the
Bessel function of the first kind.

See Also
--------
:external+libweif:cpp:class:`weif::af::circular` : Base class in C++ library.
)";

constexpr const char* circular_init_doc = R"(
Constructs an circular aperture filter.
)";

constexpr const char* circular_call1_doc = R"(
Call operator for circular aperture filter in radial coordinates.

Parameters
----------
u : float
    Dimensionless spatial frequency magnitude (radial coordinate)

Evaluates the squared jinc function for given radial frequency:

.. math::

     A(u) = \mathrm{jinc}_1^2(\pi u).

Returns
-------
float
    Aperture filter value at specified frequency

See Also
--------
:external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
)";

constexpr const char* circular_call2_doc = R"(
Call operator for circular aperture filter in Cartesian coordinates.

Evaluates the filter by converting to radial coordinates:

.. math::

     A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

Parameters
----------
ux : float
    Dimensionless spatial frequency component in x-direction.
uy : float
    Dimensionless spatial frequency component in y-direction.

Returns
-------
float
    Aperture filter value at specified frequency coordinates

See Also
--------
:external+libweif:cpp:func:`weif::af::circular::operator()` : Base function in C++ library.
)";

constexpr const char* annular_doc = R"(
Aperture filter function for an annular (ring-shaped) aperture.

The aperture filter accounts for central obscuration and is defined as:

.. math::

     A(u) &= \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2},\\
     A(u_x, u_y) &= A\left(\sqrt{u_x^2 + u_y^2}\right),

where :math:`\epsilon` is the obscuration ratio (:math:`0 \le \epsilon < 1`),
and :math:`\mathrm{jinc}_1(x) = \frac{2 J_1(x)}{x}` is the jinc function
(Fourier transform of a unit circular aperture) and :math:`J_1` is the
Bessel function of the first kind.

See Also
--------
:external+libweif:cpp:class:`weif::af::annular` : Base class in C++ library.
)";

constexpr const char* annular_init_doc = R"(
Constructs an annular aperture filter with given obscuration.

Parameters
----------
obscuration : float
    Central obscuration ratio (:math:`0 \le \epsilon < 1`)
)";

constexpr const char* annular_call1_doc = R"(
Call operator for annular aperture filter in radial coordinates.

Evaluates the squared normalized difference of jinc functions:

.. math::

     A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon^2 \mathrm{jinc}_1(\pi \epsilon u)\right)^2}{(1 - \epsilon^2)^2}.

Parameters
----------
u : float
    Dimensionless spatial frequency magnitude (radial coordinate)

Returns
-------
float
    Aperture filter value at specified frequency

See Also
--------
:external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
)";

constexpr const char* annular_call2_doc = R"(
Call operator for annular aperture filter in Cartesian coordinates.

Evaluates the filter by converting to radial coordinates:

.. math::

     A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

Parameters
----------
ux : float
    Dimensionless spatial frequency component in x-direction.
uy : float
    Dimensionless spatial frequency component in y-direction.

Returns
-------
float
    Aperture filter value at specified frequency coordinates

See Also
--------
:external+libweif:cpp:func:`weif::af::annular::operator()` : Base function in C++ library.
)";

constexpr const char* cross_annular_doc = R"(
Aperture filter for covariance between two concentric annular apertures.

Models the covariance of relative flux fluctuations between two annular apertures
as used in MASS (Multi-Aperture Scintillation Sensor) instruments:

.. math::

     A(u) = \frac{\left(\mathrm{jinc}_1(\pi u) - \epsilon_1^2 \mathrm{jinc}_1(\pi \epsilon_1 u)\right)}{(1 - \epsilon_1^2)}
            \times \frac{\left(\mathrm{jinc}_1(\pi \alpha u) - \epsilon_2^2 \mathrm{jinc}_1(\pi \epsilon_2 \alpha u)\right)}{(1 - \epsilon_2^2)},

where:
- :math:`\epsilon_1` is the central obscuration ratio of the first aperture,
- :math:`\epsilon_2` is the central obscuration ratio of the second aperture,
- :math:`\alpha = D_2/D_1` is the diameter ratio between apertures.

Reference: Tokovinin, et. al. (2003) "Restoration of turbulence profile from scintillation indices", https://doi.org/10.1046/j.1365-8711.2003.06731.x

See Also
--------
:external+libweif:cpp:class:`weif::af::cross_annular` : Base class in C++ library.
)";

constexpr const char* cross_annular_init_doc = R"(
Constructs an aperture filter for covariance of two annular apertures.

Parameters
----------
ratio : float
    Diameter ratio :math:`\alpha = D_2/D_1` between apertures.
obscuration_first : float
    Obscuration ratio :math:`\epsilon_1` of first aperture (:math:`0 \le \epsilon_1 < 1`).
obscuration_second : float
    Obscuration ratio :math:`\epsilon_2` of second aperture (:math:`0 \le \epsilon_2 < 1`).
)";

constexpr const char* cross_annular_call1_doc = R"(
Call operator for the aperture filter in radial coordinates.

Evaluates the filter in radial coordinates.

Parameters
----------
u : float
    Dimensionless spatial frequency magnitude (radial coordinate)

Returns
-------
float
    Aperture filter value at specified frequency

See Also
--------
:external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
)";

constexpr const char* cross_annular_call2_doc = R"(
Call operator for the aperture filter in Cartesian coordinates.

Evaluates the filter by converting to radial coordinates:

.. math::

     A(u_x, u_y) = A\left(\sqrt{u_x^2 + u_y^2}\right).

Parameters
----------
ux : float
    Dimensionless spatial frequency component in x-direction.
uy : float
    Dimensionless spatial frequency component in y-direction.

Returns
-------
float
    Aperture filter value at specified frequency coordinates

See Also
--------
:external+libweif:cpp:func:`weif::af::cross_annular::operator()` : Base function in C++ library.
)";

constexpr const char* point_doc = R"(
Aperture filter function for a point (infinitely small) aperture.

The aperture filter is defined in both radial and Cartesian plane coordinates:

.. math::

     A(u) = A(u_x, u_y) = 1.

This represents an ideal point aperture.

See Also
--------
:external+libweif:cpp:class:`weif::af::point` : Base class in C++ library.
)";

constexpr const char* point_init_doc = R"(
Constructs a point aperture filter.
)";

constexpr const char* point_call1_doc = R"(
Call operator for point aperture filter in radial coordinates.

Evaluates the filter function for a given radial frequency:

.. math::

     A(u) = 1.

Parameters
----------
u : float
    Dimensionless spatial frequency magnitude (radial coordinate)

Returns
-------
float
    Aperture filter value (always 1 for point aperture)

See Also
--------
:external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
)";

constexpr const char* point_call2_doc = R"(
Call operator for point aperture filter in Cartesian coordinates.

Evaluates the filter function for given frequency components:

.. math::

     A(u_x, u_y) = 1.

Parameters
----------
ux : float
    Dimensionless spatial frequency component in x-direction.
uy : float
    Dimensionless spatial frequency component in y-direction.

Returns
-------
float
    Aperture filter value (always 1 for point aperture)

See Also
--------
:external+libweif:cpp:func:`weif::af::point::operator()` : Base function in C++ library.
)";

constexpr const char* square_doc = R"(
Aperture filter function for a square aperture.

The aperture filter is defined in Cartesian coordinates as:

.. math::

     A(u_x, u_y) = \mathrm{sinc}^2(\pi u_x) \cdot \mathrm{sinc}^2(\pi u_y),

representing the Fourier transform of a square pupil function.

See Also
--------
:external+libweif:cpp:class:`weif::af::square` : Base class in C++ library.
)";

constexpr const char* square_init_doc = R"(
Constructs a square aperture filter.
)";

constexpr const char* square_call_doc = R"(
Call operator for square aperture filter in Cartesian coordinates.

Evaluates the squared 2D sinc function:

.. math::

     A(u_x, u_y) = \mathrm{sinc}^2(\pi u_x) \cdot \mathrm{sinc}^2(\pi u_y).

Parameters
----------
ux : float
    Dimensionless spatial frequency in x-direction.
uy : float
    Dimensionless spatial frequency in y-direction.

Returns
-------
float
    Aperture filter value at specified frequencies

See Also
--------
:external+libweif:cpp:func:`weif::af::square::operator()` : Base function in C++ library.
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


void init_af(nb::module_& m) {
	/* Python floating point number is the double. So, let value_type = double.
	 * numpy are templated due to xt::xexpression<E>, allow float, double, long double.
	 */
	using value_type = double;

	/* Note, that py::overload_cast<> cannot be used here due to
	 * https://github.com/pybind/pybind11/issues/1153
	 */

	using circular_type = af::circular<value_type>;
	nb::class_<circular_type>(m, "Circular", circular_doc)
		.def(nb::init<>(), circular_init_doc)
		.def("__call__", get_call<value_type, circular_type(value_type)>(), nb::arg("u"), circular_call1_doc)
		.def("__call__", get_call<value_type, circular_type(value_type, value_type)>(), nb::arg("ux"), nb::arg("uy"), circular_call2_doc);

	using annular_type = af::annular<value_type>;
	nb::class_<af::annular<value_type>>(m, "Annular", annular_doc)
		.def(nb::init<value_type>(), nb::arg("obscuration"), annular_init_doc)
		.def("__call__", get_call<value_type, annular_type(value_type)>(), nb::arg("u"), annular_call1_doc)
		.def("__call__", get_call<value_type, annular_type(value_type, value_type)>(), nb::arg("ux"), nb::arg("uy"), annular_call2_doc);

	using cross_annular_type = af::cross_annular<value_type>;
	nb::class_<af::cross_annular<value_type>>(m, "CrossAnnular", cross_annular_doc)
		.def(nb::init<value_type, value_type, value_type>(), nb::arg("ratio"), nb::arg("obscuration_first"), nb::arg("obscuration_second"), cross_annular_init_doc)
		.def("__call__", get_call<value_type, cross_annular_type(value_type)>(), nb::arg("u"), cross_annular_call1_doc)
		.def("__call__", get_call<value_type, cross_annular_type(value_type, value_type)>(), nb::arg("ux"), nb::arg("uy"), cross_annular_call2_doc);

	using point_type = af::point<value_type>;
	nb::class_<point_type>(m, "Point", point_doc)
		.def(nb::init<>(), point_init_doc)
		.def("__call__", get_call<value_type, point_type(value_type)>(), nb::arg("u"), point_call1_doc)
		.def("__call__", get_call<value_type, point_type(value_type, value_type)>(), nb::arg("ux"), nb::arg("uy"), point_call2_doc);

	using square_type = af::square<value_type>;
	nb::class_<square_type>(m, "Square", square_doc)
		.def(nb::init<>(), square_init_doc)
		.def("__call__", get_call<value_type, square_type(value_type, value_type)>(), nb::arg("ux"), nb::arg("uy"), square_call_doc);
}
