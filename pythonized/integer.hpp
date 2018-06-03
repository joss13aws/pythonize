#ifndef PYTHONIZE_INTEGER
#define PYTHONIZE_INTEGER

#include <limits>       // std::numeric_limits
#include <cstdint>      // std::(u)intN_t
#include <iostream>     // std::istream, std::ostream
#include <stdexcept>    // std::invalid_argument, std::out_of_range
#include <string_view>  // std::string_view
#include <type_traits>  // std::conditional, std::is_same, std::is_void,
                        // std::is_signed, std::is_arithmetic
#include <system_error> // std::errc
#include <iterator>     // std::begin, std::end
#include <charconv>     // std::from_chars
#include <cctype>       // std::isspace

// TODO: If possible in future versions of C++:
//       ‘int’               = ‘Int’
//       ‘int<64, unsigned>’ = ‘Int<64, unsigned>’
//       ‘int a’             = ‘Int<> a’
//       ‘std::vector<int>’  = ‘std::vector<Int<>>’
//       [The same for uint]

// TODO: Conflicts with <memory>
// error: ‘class pythonize::Int<32>’ is not a valid type
// for a template non-type parameter: template<int _Nm, typename _Tp,

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
	class Int
	{
		template <typename It>
		static auto skip_ws(It it)
		{
			for (; std::isspace(*it); ++it);
			return it;
		}

	public:
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

		template <auto any_size, typename any_sign>
		constexpr Int(Int<any_size, any_sign> other) : value(other.value) {}

		constexpr Int(std::string_view arg)
		{
			auto [ptr, err] = std::from_chars
				(skip_ws(std::begin(arg)), std::end(arg), value);

			if (err == std::errc::invalid_argument)
			    throw std::invalid_argument("Int(str)");
			if (err == std::errc::result_out_of_range)
			    throw std::out_of_range("Int(str)");

			if (skip_ws(ptr) != std::end(arg))
				throw std::invalid_argument("Int(str)");
		}

		constexpr operator type&() { return value; }
		constexpr operator const type&() const { return value; }
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
