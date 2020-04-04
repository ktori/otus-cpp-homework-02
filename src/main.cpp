//
// Created by victoria on 04.04.20.
//

#include "custom_tuple.hpp"
#include "custom_tie.hpp"

#include <string>
#include <cassert>

auto getPerson() {
	const std::string name = "Petia";
	const std::string secondName = "Ivanoff";
	const std::size_t age = 23;
	const std::string department = "Sale";

	return ktori::make_tuple(
		name, secondName, age, department
	);
}

int main(int argc, char *argv[])
{
	std::string name, secondName, department;
	std::size_t age;

	ktori::tie(name, secondName, age, department) = getPerson();

	assert(name == "Petia");
	assert(secondName == "Ivanoff");
	assert(age == 23);
	assert(department == "Sale");

	return 0;
}