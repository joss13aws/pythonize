// #define EXPERIMENTAL

#include "pythonize.hpp" // To test the current version
// #include <pythonize>  // Installed version

int main() // Testing
{
	auto number = input("Enter float: ");
	auto qwerty = str("Hello World!");
	str text;
	print(float(number), qwerty, 42);
	print(num("  123    ") == 123);

	for (auto i : range(10))
		print(i);
}
