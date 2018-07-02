// #define EXPERIMENTAL

#include "pythonize.hpp" // To test the current version
// #include <pythonize>  // Installed version

int main() // Testing
{
	float number = input("Enter float: ");
	auto qwerty = str("Hello World!");
	str text;
	print(number, qwerty, 42);
	print(num("  123    ") == 123);

	for (auto i : range(10))
		print(i);

	for (int a : open("file.txt"))
		print(a);

	#ifdef TODO_PROPOSALS

	for (int c : file) // numbers from file
	for (char c : file) // file char by char
	for (str s : file) // file line by line
	int a = file.input() // number from file

	#endif
}
