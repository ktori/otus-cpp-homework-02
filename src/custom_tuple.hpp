//
// Created by victoria on 04.04.20.
//

#pragma once

#include <cstddef>
#include <functional>

namespace ktori
{
	template<size_t index, typename... Ts>
	class tuple_impl
	{

	};

	template<size_t index, typename T>
	struct assignable_value;

	template<size_t index, typename X>
	struct assignable_value<index, std::reference_wrapper<X>>
	{
		using value_type = X;
		using ref_type = std::reference_wrapper<X>;

		explicit assignable_value(ref_type value) : _value(value) {}

		value_type& value()
		{
			return _value.get();
		}

		const value_type& value() const
		{
			return _value.get();
		}

		std::reference_wrapper<X> _value;
	};

	template<size_t index, typename T>
	struct assignable_value
	{
		using value_type = T;

		explicit assignable_value(T value) : _value(value) {}

		value_type& value()
		{
			return _value;
		}

		const value_type& value() const
		{
			return _value;
		}

		T _value;
	};

	template<size_t index, typename T, typename... Ts>
	class tuple_impl<index, T, Ts...> : public tuple_impl<index + 1, Ts...>, private assignable_value<index, T>
	{
	public:
		using assignable_type = assignable_value<index, T>;

		explicit tuple_impl(T value, Ts... rest) : tuple_impl<index + 1, Ts...>(rest...), assignable_type(value) {}

		typename assignable_type::value_type& get()
		{
			return assignable_type::value();
		}

		const typename assignable_type::value_type& get() const
		{
			return assignable_type::value();
		}

		template<size_t x, typename X, typename... Xs>
		tuple_impl<index, T, Ts...>& operator=(const tuple_impl<x, X, Xs...>& other)
		{
			get() = other.get();
			tuple_impl<index + 1, Ts...>::operator=(static_cast<const tuple_impl<x + 1, Xs...>&>(other));
			return *this;
		}
	};

	template<size_t index, typename T, typename... Ts>
	T& get(tuple_impl<index, T, Ts...>& tuple)
	{
		return tuple.get();
	}

	template<typename T, typename... Ts>
	using tuple = tuple_impl<0, T, Ts...>;

	template<typename T, typename... Ts>
	tuple<T, Ts...> make_tuple(T value, Ts... rest)
	{
		return tuple_impl<0, T, Ts...>(value, rest...);
	}
}
