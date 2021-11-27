#include "vector.h"
#include <memory>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	std::allocator<int> alloc;
	astl::vector<int> vec;
	std::vector<int> vec2;
	vec2.push_back(3);
	vec.push_back(3);
	vec.push_back(4);
	for (int val : vec) {
		std::cout << "val " << val << std::endl;
	}
	std::cout << std::is_copy_assignable<int>::value << std::endl;
}