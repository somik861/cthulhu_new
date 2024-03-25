#include "Dict.hpp"
#include "builtin_structs/Dict.hpp"
#include "builtin_structs/Stack.hpp"
#include <cassert>
#include <iostream>
#include <memory>

namespace tests::Dict {
void run_tests() {
	builtin_structs::Dict<true> dct;

	auto counter = 0;
	auto make_stack = [&counter]() {
		auto rv = std::make_unique<builtin_structs::Stack<true>>();
		rv->push(counter++);
		return rv;
	};

	// set and get
	assert(dct.size() == 0);
	dct.set(1, make_stack());
	assert(dct.size() == 1);
	assert(dct.contains(1));
	assert(!dct.contains(0));
	dct.set(0, make_stack());
	assert(dct.contains(0));
	assert(dct.contains(1));
	assert(dct.size() == 2);
	assert(dct.at(0)->peek<int>() == 1);
	assert(dct.at(1)->peek<int>() == 0);
	dct.clear();
	assert(dct.size() == 0);
	assert(!dct.contains(0));
	assert(!dct.contains(1));

	// copy and move
	decltype(dct) dct2;

	dct.set(0, make_stack());
	dct.set(1, make_stack());
	dct2 = dct;
	assert(dct2.size() == 2);
	assert(dct2.at(1)->peek<int>() == 3);
	dct.clear();
	dct = std::move(dct2);
	assert(dct.size() == 2);
	dct.clear();
	assert(dct.size() == 0);

	std::cout << "DICT OK\n";
}
} // namespace tests::Dict