#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <iostream>
#include "string.hpp"

namespace pythonize
{
	/* TODO: Just constexpr?
	constexpr const char * bool_to_str(bool value)
	{

	}*/

	inline str input(std::string prompt = "")
	{
		std::cout << prompt;
		std::string res;
		std::cin >> res;
		return res;
	}

	template <typename T = char *>
	inline void print(const T value = "")
	{
		std::cout << value << '\n';
	}

	/* Draft:
	template <>
	inline void print<bool>(const T value)
	{
		std::cout << (value ? "True" : "False") << '\n';
	}*/

	template <typename T, typename... Args>
	inline void print(const T value, const Args... args)
	{
		std::cout << value << ' ';
		print(args...);
	}
}

#endif
