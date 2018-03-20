#include <pythonize>

int main() // Testing
{
	auto number = input("Enter float: ");
	auto qwerty = str("Hello World!");
	print(float(number), qwerty, 42);

	print(str(12) == "12");

	for (auto i : range(10))
		print(i);
}
