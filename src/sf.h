/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef _PYWEIF_SF_H
#define _PYWEIF_SF_H

#include <functional>
#include <variant>

#include <weif/sf/mono.h>
#include <weif/sf/gauss.h>
#include <weif/sf/poly.h>

#include "function_ref.h"


template<class T>
struct py_sf {
	using function_ref_type = function_ref<T(T)>;

	function_ref_type fun;

	T operator() (T u) const noexcept {
		return fun(u);
	}
};

NAMESPACE_BEGIN(NB_NAMESPACE)
NAMESPACE_BEGIN(detail)

template <class T>
struct type_caster<py_sf<T>>: function_ref_caster<py_sf<T>, T(T),
	weif::sf::mono<T>,
	weif::sf::gauss<T>,
	weif::sf::poly<T>> {};

NAMESPACE_END(detail)
NAMESPACE_END(NB_NAMESPACE)

#endif // _PYWEIF_SF_H
