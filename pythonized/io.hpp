#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <string>      // std::string
#include <cctype>      // std::isspace
#include <cstddef>     // std::ptrdiff_t, std::nullptr_t
#include <istream>     // std::istream, std::ws
#include <iostream>    // std::cin, std::cout
#include <stdexcept>   // std::invalid_argument
#include <string_view> // std::string_view
#include <type_traits> // std::is_same
#include "string.hpp"  // py::str

namespace py
{
	class istream_iterator
	{
		// TODO: Reduce code size (here and in input())

		std::istream &in;

		// TODO: Iterate through chars without reading everything twice!
		inline void skip_ws()
		{
			for (char c; (c = in.peek()) != '\n' && std::isspace(c); in.get());
		}

	public:
		constexpr istream_iterator(std::istream &stream) : in(stream) {}

		template <typename T>
		inline operator T()
		{
			T res;
			in >> res;
			return res;
		}

		inline operator str()
		{
			str res;
			in >> res;
			return res;
		}

		inline operator char() { return in.get(); }

		using value_type = istream_iterator;
		using difference_type = std::ptrdiff_t;
		using pointer = istream_iterator *;
		using reference = istream_iterator &;
		using iterator_category	= std::input_iterator_tag;

		inline bool operator==(std::nullptr_t end) const
		{
			return in.peek() == '\n';
		}

		inline bool operator!=(std::nullptr_t end) const
		{
			return !(*this == end);
		}

		constexpr auto operator++() const { return *this; }
		constexpr auto operator*() const { return *this; }

		// Dummies to satisfy Iterator requirements
		constexpr auto operator++(int) const { return *this; }
		constexpr auto operator->() const { return this; }
	};

	struct input
	{
		inline input(std::string_view prompt = "") { std::cout << prompt; }
		auto begin() { return istream_iterator(std::cin); }
		auto end() { return nullptr; }

		template <typename T>
		inline operator T()
		{
			T res;
			std::cin >> res;
			return res;
		}

		inline operator str()
		{
			str res;
			std::getline(std::cin, res);
			return res;
		}

		class split; // TODO (lazy)
	};

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
}

#endif
