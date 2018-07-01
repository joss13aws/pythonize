#ifndef PYTHONIZE_IO
#define PYTHONIZE_IO

#include <string>      // std::string
#include <cctype>      // std::isspace
#include <istream>     // std::istream
#include <fstream>     // std::ifstream
#include <cstddef>     // std::ptrdiff_t, std::nullptr_t
#include <iostream>    // std::cin, std::cout
#include <string_view> // std::string_view
#include <type_traits> // std::is_same
#include "string.hpp"  // py::str

namespace py
{
	class istream_iterator
	{
		// TODO: Reduce code size (here, in derived and in input())

	protected:
		std::istream &in;

		// TODO: Iterate through chars without reading everything twice!
		inline void skip_ws(char stop = '\n')
		{
			for (char c; (c = in.peek()) != stop && std::isspace(c); in.get());
		}

	public:
		constexpr istream_iterator(std::istream &stream) : in(stream) {}

		template <typename T>
		inline operator T()
		{
			T res;
			in >> res;
			skip_ws();
			return res;
		}

		inline operator str()
		{
			str res;
			in >> res;
			skip_ws();
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

	struct ifstream_iterator : public istream_iterator
	{
		using istream_iterator::istream_iterator;

		template <typename T>
		inline operator T()
		{
			T res;
			in >> res;
			skip_ws(EOF);
			return res;
		}

		inline operator str()
		{
			str res;
			std::getline(in, res);
			return res;
		}

		inline operator char() { return in.get(); }

		using value_type = ifstream_iterator;
		using pointer = ifstream_iterator *;
		using reference = ifstream_iterator &;

		inline bool operator==(std::nullptr_t end) const
		{
			return in.peek() == EOF;
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
		std::istream &stream;
		inline input(std::string_view prompt = "", std::istream &in = std::cin)
			: stream(in) { std::cout << prompt; }
		constexpr auto begin() { return istream_iterator(stream); }
		constexpr auto end() { return nullptr; }

		template <typename T>
		inline operator T()
		{
			T res;
			stream >> res;
			return res;
		}

		inline operator str()
		{
			str res;
			std::getline(stream, res);
			return res;
		}

		class split; // TODO (lazy)
	};

	struct file
	{
		std::ifstream stream;
		inline file(const std::string &filename) : stream(filename) {}
		constexpr auto begin() { return ifstream_iterator(stream); }
		constexpr auto end() { return nullptr; }
		inline auto input() { return py::input("", stream); };
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
