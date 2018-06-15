#ifndef PYTHONIZE_EXPERIMENTAL
#define PYTHONIZE_EXPERIMENTAL

#include "integer.hpp"

// TODO: If possible in future versions of C++:
//       ‘int’               = ‘Int’
//       ‘int<64, unsigned>’ = ‘Int<64, unsigned>’
//       ‘int a’             = ‘Int<> a’
//       ‘std::vector<int>’  = ‘std::vector<Int<>>’
//       [The same for uint]

// TODO: Conflicts with templates that have int parameters
// Example: <memory>
// error: ‘class py::Int<32>’ is not a valid type
// for a template non-type parameter: template<int _Nm, typename _Tp,

// TODO: Conflicts with macros that use int (like htons())

namespace py
{
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
	// TODO: Breaks if main takes arguments
}

#endif
