/*
 * Copyright (c) 2024, Matwey V. Kornilov <matwey.kornilov@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef _PYWEIF_FUNCTION_REF_H
#define _PYWEIF_FUNCTION_REF_H

#include <boost/compat/function_ref.hpp>

#include <nanobind/nanobind.h>

template <class... Args>
using function_ref = boost::compat::function_ref<Args...>;

template <auto V>
using nontype_t = boost::compat::nontype_t<V>;

NAMESPACE_BEGIN(NB_NAMESPACE)
NAMESPACE_BEGIN(detail)

template <typename Return, typename... Args>
struct type_caster<function_ref<Return(Args...)>> {
	using ReturnCaster = make_caster<std::conditional_t<std::is_void_v<Return>, void_type, Return>>;
	using Value = function_ref<Return(Args...)>;
	static constexpr auto Name = const_name(NB_TYPING_CALLABLE "[[") + concat(make_caster<Args>::Name...) + const_name("], ") + ReturnCaster::Name + const_name("]");

	template <typename T> using Cast = movable_cast_t<T>;
	template <typename T> static constexpr bool can_cast() { return true; }
	explicit operator Value*() { return &value; }
	explicit operator Value&() { return (Value&)value; }
	explicit operator Value&&() { return std::move(value); }

	bool from_python(handle src, uint8_t flags, cleanup_list *) noexcept {
		if (src.is_none())
			return flags & cast_flags::convert;

		if (!PyCallable_Check(src.ptr()))
			return false;

		value = Value{nontype_t<[] (PyObject *f, Args&&... args) -> Return {
			return cast<Return>(handle(f) (std::forward<Args>(args)...));
		}>{}, src.ptr()};

		return true;
	}

	static handle from_cpp(const Value &value, rv_policy rvp, cleanup_list *) noexcept {
		return cpp_function(value).release();
	}

	/* FIXME: use variant<mono instead ???*/
	Value value = Value{(Return(*)(Args...))nullptr};
};

template <typename T, typename F, class... Args>
struct function_ref_caster {
	using FunctionRefType = function_ref<F>;
	using FunctionRefCaster = make_caster<FunctionRefType>;
	using Value = T;
	static constexpr auto Name = FunctionRefCaster::Name;

	template <typename _T> using Cast = movable_cast_t<_T>;
	template <typename _T> static constexpr bool can_cast() { return true; }
	explicit operator Value*() { return &value; }
	explicit operator Value&() { return (Value&)value; }
	explicit operator Value&&() { return std::move(value); }

	template <typename U>
	bool try_variant(const handle &src, uint8_t flags, cleanup_list *cleanup) {
		using CasterU = make_caster<U>;

		CasterU caster;

		if (!caster.from_python(src, flags_for_local_caster<U>(flags), cleanup) || !caster.template can_cast<U>())
			return false;

		value = Value{FunctionRefType{nontype_t<[] (U *obj, auto&&... args) -> decltype(auto) {
			return obj->operator()(std::forward<decltype(args)>(args)...);
		}>{}, static_cast<U*>(caster)}};

		return true;
	}

	bool from_python(handle src, uint8_t flags, cleanup_list* cleanup) noexcept {
		/* Try list of known types */
		if ((try_variant<Args>(src, flags, cleanup) || ...))
			return true;

		/* Fallback to generic Python call */
		FunctionRefCaster caster;

		if (!caster.from_python(src, flags_for_local_caster<FunctionRefType>(flags), cleanup) || !caster.template can_cast<FunctionRefType>())
			return false;

		value = Value{caster.operator cast_t<FunctionRefType>()};

		return true;
	}

	static handle from_cpp(const Value &value, rv_policy rvp, cleanup_list* cleanup) noexcept {
		FunctionRefCaster caster;

		return caster.from_cpp(value.fun, rvp, cleanup);
	}

	Value value = Value{function_ref<F>{(std::add_pointer_t<F>)nullptr}};
};

NAMESPACE_END(detail)
NAMESPACE_END(NB_NAMESPACE)

#endif // _PYWEIF_FUNCTION_REF_H
