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

	template<typename T>
	struct value_wrapper
	{
		explicit value_wrapper(T value): _value(value) {}

		inline T& value()
		{
			return _value;
		}

		T _value;
	};

	template<typename T>
	struct value_wrapper<std::reference_wrapper<T>>
	{
		explicit value_wrapper(std::reference_wrapper<T> value): _value(value) {}

		inline T& value()
		{
			return _value.get();
		}

		std::reference_wrapper<T> _value;
	};

	template<size_t index, typename T, typename... Ts>
	class tuple_impl<index, T, Ts...> : public tuple_impl<index + 1, Ts...>, public value_wrapper<T>
	{
	public:
		explicit tuple_impl(T value, Ts... rest) : tuple_impl<index + 1, Ts...>(rest...), value_wrapper<T>(value) {}

		inline T& get()
		{
			return value_wrapper<T>::value();
		}

		template<size_t x, typename X, typename... Xs>
		tuple_impl<index, T, Ts...>& operator=(const tuple_impl<x, X, Xs...>& other)
		{
			get() = other.get();
			tuple_impl<index + 1, Ts...>::operator=(other);
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
