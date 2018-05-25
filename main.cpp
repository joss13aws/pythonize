#include "pythonize.hpp" // To test the current version
// #include <pythonize>  // Installed version

int main() // Testing
{
	auto number = input("Enter float: ");
	auto qwerty = str("Hello World!");
	print(float(number), qwerty, 42);

	print(str(long("144")) == "144");

	long double a;

	Int<> b;

	for (auto i : range(10))
		print(i);
}
