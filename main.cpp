// #define EXPERIMENTAL

#include "pythonize.hpp" // To test the current version
// #include <pythonize>  // Installed version

int main() // Testing
{
	float number = lazy::input("Enter float: ");
	auto qwerty = str("Hello World!");
	str text;
	print(number, qwerty, 42);
	print(num("  123    ") == 123);

	for (auto i : range(10))
		print(i);

	//for (auto c : input())
	//	print(c);

	#ifdef TODO_PROPOSALS

	for (int c : input()) // numbers in line
	for (char c : input()) // chars in line
	for (str s : input()) // words in line
	str s1 = input(); // line
	int a = input(); // number
	str s2 = input().split[0]; // word (split = lazy list)

	for (int c : file) // numbers from file
	for (char c : file) // file char by char
	for (str s : file) // file line by line
	int a = file.read() // number from file

	#endif
}
