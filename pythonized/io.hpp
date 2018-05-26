#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <string>      // std::string
#include <iostream>    // std::cin, std::cout
#include <string_view> // std::string_view
#include <type_traits> // std::is_same
#include "string.hpp"  // pythonize::str

namespace pythonize
{
	inline str input(std::string_view prompt = "")
	{
		std::cout << prompt;
		std::string res;
		std::cin >> res;
		return res;
	}

	template <typename T, typename... Args>
	inline void print(const T value, const Args... args)
	{
		if constexpr (std::is_same<T, bool>::value)
			std::cout << (value ? "True" : "False");
		else
			std::cout << value;

		if constexpr (sizeof...(Args) > 0)
		{
			std::cout << ' ';
			print(args...);
		}

		else std::cout << '\n';
	}
}

#endif
