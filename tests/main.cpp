#include "Stack.hpp"
#include "Dict.hpp"
#include <iostream>

int main() {
	tests::Stack::run_tests();
	tests::Dict::run_tests();

	std::cout << "ALL TESTS OK\n";
}