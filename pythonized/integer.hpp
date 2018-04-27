#ifndef PYTHONIZE_INTEGER
#define PYTHONIZE_INTEGER

#include <limits>
#include <cstdint>
#include <iostream>
#include <type_traits>

// TODO: Make ‘std::vector<int>’ legal if possible

namespace pythonize
{
	namespace size
	{
		constexpr int def = sizeof(int) * 8;
		constexpr int ptr = sizeof(intptr_t) * 8;
		constexpr int max = sizeof(intmax_t) * 8;
	}

	template <int size = size::def, typename sign = signed>
	struct Int
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

		static_assert(!std::is_void<type>::value,
			"\n  Integer must be 8, 16, 32 or 64 bits.");

		using limits = std::numeric_limits<type>;
		static constexpr auto min = limits::min, max = limits::max;

		type value;
		constexpr Int() = default;
		constexpr Int(type arg) : value(arg) {}
		constexpr operator type&() { return value; }
		constexpr operator const type&() const { return value; }
	};

	// A separate class instead of a templated alias
	// allows using ‘uint’ instead of ‘uint<>’ (since C++17).

	template <int size = size::def>
	struct UInt : Int<size, unsigned>
	{
		using Base = Int<size, unsigned>;
		constexpr UInt() = default;
		constexpr UInt(typename Base::type arg) : Base(arg) {}
	};

	#define int Int
	#define uint UInt

	// And, since main() must return an int...
	#define main() <>::type main()
}

// Treat (u)int<8> as a number, not as a char

namespace std
{
	template <typename sign>
	inline istream & operator>>(istream &stream, pythonize::int<8, sign> &arg)
	{
		int16_t buff;
		stream >> buff;
		arg.value = buff;
		return stream;
	}

	template <typename sign>
	inline ostream & operator<<(ostream &stream, pythonize::int<8, sign> arg)
	{
		stream << int16_t(arg.value);
		return stream;
	}
}

#endif
