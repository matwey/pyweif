/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef _PYWEIF_AF_H
#define _PYWEIF_AF_H

#include <functional>
#include <variant>

#include <weif/af/circular.h>
#include <weif/af/point.h>
#include <weif/af/square.h>

#include "function_ref.h"


template<class T>
struct py_af {
	using function_ref_type = function_ref<T(T)>;

	function_ref_type fun;

	T operator() (T u) const noexcept {
		return fun(u);
	}
};

template<class T>
struct py_af_2d {
	using function_ref_type = function_ref<T(T, T)>;

	function_ref_type fun;

	T operator() (T ux, T uy) const noexcept {
		return fun(ux, uy);
	}
};


NAMESPACE_BEGIN(NB_NAMESPACE)
NAMESPACE_BEGIN(detail)

template <class T>
struct type_caster<py_af<T>>: function_ref_caster<py_af<T>, T(T),
	weif::af::annular<T>,
	weif::af::circular<T>,
	weif::af::cross_annular<T>,
	weif::af::point<T>> {};

template <class T>
struct type_caster<py_af_2d<T>>: function_ref_caster<py_af_2d<T>, T(T, T),
	weif::af::annular<T>,
	weif::af::circular<T>,
	weif::af::cross_annular<T>,
	weif::af::point<T>,
	weif::af::square<T>> {};

NAMESPACE_END(detail)
NAMESPACE_END(NB_NAMESPACE)


#endif // _PYWEIF_AF_H

