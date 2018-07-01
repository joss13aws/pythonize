#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <string>      // std::string
#include <cctype>      // std::isspace
#include <istream>     // std::ws
#include <iostream>    // std::cin, std::cout
#include <stdexcept>   // std::invalid_argument
#include <string_view> // std::string_view
#include <type_traits> // std::is_same
#include "string.hpp"  // py::str

namespace py
{
	inline str input(std::string_view prompt = "")
	{
		std::cout << prompt;
		std::string res;
		std::getline(std::cin, res);
		return res;
	}

	template <typename T = char const *, typename... Args>
	inline void print(const T value = "", const Args... args)
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

	namespace lazy
	{
		bool nws_left(std::istream &in)
		{
			for (char c; (c = in.peek()) != '\n' && c != EOF; in.get())
				if (!std::isspace(c))
					return true;
			return false;
		}

		// TODO: char_iterator

		struct input // TODO
		{
			inline input(std::string_view prompt = "")
			{
				std::cout << prompt;
			}

			template <typename T>
			inline operator T()
			{
				T res;
				std::cin >> res;
				if (nws_left(std::cin))
					throw std::invalid_argument("T(lazy::input)");
				return res;
			}

			inline operator str()
			{
				std::string res;
				std::getline(std::cin, res);
				return res;
			}

			// begin()
			// end()
			//
		};
	}
}

#endif
