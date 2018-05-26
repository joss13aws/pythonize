#ifndef PYTHONIZE_INTEGER
#define PYTHONIZE_INTEGER

#include <string>      // std::string
#include <limits>      // std::numeric_limits
#include <cstdint>     // std::(u)intN_t
#include <sstream>     // std::istringstream
#include <istream>     // std::ws
#include <iostream>    // std::istream, std::ostream
#include <stdexcept>   // std::invalid_argument
#include <string_view> // std::string_view
#include <type_traits> // std::conditional, std::is_same, std::is_void,
                       // std::is_signed, std::is_arithmetic

// TODO: If possible in future versions of C++:
//       ‘int’               = ‘Int’
//       ‘int<64, unsigned>’ = ‘Int<64, unsigned>’
//       ‘int a’             = ‘Int<> a’
//       ‘std::vector<int>’  = ‘std::vector<Int<>>’
//       [The same for uint]

namespace pythonize
{
	namespace size
	{
		constexpr auto def = sizeof(int) * 8;
		constexpr auto ptr = sizeof(intptr_t) * 8;
		constexpr auto max = sizeof(intmax_t) * 8;
	}

	template <auto size, typename sign>
	struct IntSelect
	{
		template <bool a, typename b, typename c>
		using conditional = std::conditional<a, b, c>;

		using type =
			typename conditional<std::is_signed<sign>::value,
				typename conditional<size == 8, std::int8_t,
					typename conditional<size == 16, std::int16_t,
						typename conditional<size == 32, std::int32_t,
							typename conditional<size == 64, std::int64_t,
							void>::type
						>::type
					>::type
				>::type,
				typename conditional<size == 8, std::uint8_t,
					typename conditional<size == 16, std::uint16_t,
						typename conditional<size == 32, std::uint32_t,
							typename conditional<size == 64, std::uint64_t,
							void>::type
						>::type
					>::type
				>::type
			>::type;
	};

	template <auto size = size::def, typename sign = signed>
	struct Int
	{
		using type = typename IntSelect<size, sign>::type;
		using default_type = typename IntSelect<size::def, signed>::type;

		// For ‘long double’, since we redefine ‘long’ below
		using double_type = typename std::conditional
			<std::is_same<type, long>::value, long double, void>::type;

		static_assert(!std::is_void<type>::value,
			"\n  Integer must be 8, 16, 32 or 64 bits.");

		using limits = std::numeric_limits<type>;
		static constexpr auto min = limits::min, max = limits::max;

		type value;
		constexpr Int() = default;
		constexpr Int(type arg) : value(arg) {}
		constexpr operator type&() { return value; }
		constexpr operator const type&() const { return value; }

		constexpr Int(const std::string &arg)
		{
			std::istringstream buffer(arg);
			buffer >> (*this) >> std::ws;
			if (!buffer.eof())
				throw std::invalid_argument("Int(str)");

			// TODO: Check if this way is fast enough

			// Alternative option #1:
			// #include <cstdio>
			// #include <cinttypes>
			// auto format =
			//      SCNd8   SCNu8
			//      SCNd16  SCNu16
			//      SCNd32  SCNu32
			//      SCNd64  SCNu64
			// char end[1];
			// std::sscanf(arg.c_str(), "%" format "%s", &value);
			// if (end[0] != '\0')
			// 	throw std::invalid_argument("Int(str)");

			// Alternative option #2:
			// #include <charconv>
			// #include <iterator>
			// std::from_chars(std::begin(arg), std::end(arg), value);
		}
	};

	template <auto size = size::def>
	using UInt = Int<size, unsigned>;

	// Fixed-width integer types:

	using byte   = Int<8>;
	using ubyte  = UInt<8>;

	#define short  Int<16>
	#define int    Int<32>
	#define long   Int<64>

	#define ushort UInt<16>
	#define uint   UInt<32>
	#define ulong  UInt<64>

	// For ‘(long) double’ with redefined ‘long’
	using double_type = double;
	#define double ::double_type

	// And, since main() must return an int...
	#define main() ::default_type main()
}

// Treat (u)int<8> as a number, not as a char

namespace std
{
	// TODO: Overload more type traits?
	template <auto size, typename sign>
	struct is_arithmetic<pythonize::Int<size, sign>>
	{
		static constexpr bool value = true;
	};

	template <typename sign>
	inline istream & operator>>(istream &stream, pythonize::Int<8, sign> &arg)
	{
		int16_t buff;
		stream >> buff;
		arg.value = buff;
		return stream;
	}

	template <typename sign>
	inline ostream & operator<<(ostream &stream, pythonize::Int<8, sign> arg)
	{
		stream << int16_t(arg.value);
		return stream;
	}
}

#endif
