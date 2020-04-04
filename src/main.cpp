//
// Created by victoria on 04.04.20.
//

#include "custom_tuple.hpp"
#include "custom_tie.hpp"

#include <iostream>

int main()
{
	std::string string = "hello";

	auto tuple = ktori::make_tuple(1, false, 2.0f, string);

	std::cout
		<< ktori::get<0>(tuple) << " "
		<< ktori::get<1>(tuple) << " "
		<< ktori::get<2>(tuple) << " "
		<< ktori::get<3>(tuple) << "\n";

	int a;
	bool b;
	float c;
	std::string d;

	ktori::tie(a, b, c, d) = tuple;

	std::cout
		<< a << " "
		<< b << " "
		<< c << " "
		<< d << "\n";

	return 0;
}
