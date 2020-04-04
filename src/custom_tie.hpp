//
// Created by victoria on 04.04.20.
//

#pragma once

#include <functional>
#include "custom_tuple.hpp"

namespace ktori
{
	template<typename T, typename... Ts>
	tuple_impl<0, std::reference_wrapper<T>, std::reference_wrapper<Ts>...> tie(T& value, Ts&... values)
	{
		return make_tuple(std::ref(value), std::ref(values)...);
	}
}
