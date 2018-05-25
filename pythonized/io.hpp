#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <iostream>
#include <type_traits>
#include "string.hpp"

namespace pythonize
{
	inline str input(std::string prompt = "")
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
