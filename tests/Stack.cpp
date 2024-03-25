#include "Stack.hpp"
#include "builtin_structs/Stack.hpp"
#include <cassert>
#include <memory>
#include <tuple>
#include <iostream>

namespace tests::Stack {
void run_tests() {
	// REQUIRES int and int* in stack
	builtin_structs::Stack<true> s;

	// test integer
	assert(s.size() == 0);
	s.push(3);
	assert(s.size() == 1);
	assert(s.peek<int>() == 3);
	assert(s.size() == 1);
	assert(s.pop<int>() == 3);
	assert(s.size() == 0);

	// test pointer
	assert(s.size() == 0);
	auto elem = std::make_unique<int>(5);
	int* elem_ptr = elem.get();
	s.push(std::move(elem));
	assert(s.size() == 1);
	assert(s.peek<int*>() == elem_ptr);
	assert(s.size() == 1);
	assert(*s.peek<int*>() == 5);
	assert(s.size() == 1);
	auto got_elem = s.pop<std::unique_ptr<int>>();
	assert(s.size() == 0);
	assert(got_elem.get() == elem_ptr);
	assert(*got_elem == 5);

	// test pop() and clear()
	assert(s.size() == 0);
	for (int i = 1; i < 5; ++i) {
		s.push(i);
		assert(s.size() == i);
	}
	assert(s.size() == 4);
	s.pop();
	assert(s.size() == 3);
	assert(s.pop<int>() == 3);
	assert(s.size() == 2);
	s.clear();
	assert(s.size() == 0);

	// copy and move
	decltype(s) s2;
	s2.push(1);
	s2.push(std::make_unique<int>(2));
	assert(s2.size() == 2);

	s = s2;
	assert(s.size() == 2);
	assert(s2.size() == 2);
	*s.peek<int*>() = 3;
	assert(*s2.peek<int*>() == 2);

	s = std::move(s2);
	assert(s.size() == 2);
	assert(*s.pop<std::unique_ptr<int>>() == 2);
	assert(s.pop<int>() == 1);

	std::cout << "STACK OK\n";
}
} // namespace tests::Stack