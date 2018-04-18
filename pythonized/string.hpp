#ifndef PYTHONIZE_STR
#define PYTHONIZE_STR

#include <string>
#include <cstdint>
#include <sstream>

namespace pythonize
{
	struct str : public std::string
	{
		using std::string::string;

		inline str(const std::string &other) : std::string(other) {}
		inline str(const char *s) : std::string(s) {}

		template <class T>
		explicit inline str(const T &other)
			: std::string(std::to_string(other)) {}

		class split; // TODO
		str join(/* Many args or a list? */); // TODO

		/* Oh wait, shit, will int() return int anyway?
		template <int8_t size = sizeof(int)>
		explicit inline operator int() const
		{
			// Doesn’t work because of the scope
			     if constexpr (size ==  8) ; // TODO
			else if constexpr (size == 16) int16_t value;
			else if constexpr (size == 32) int32_t value;
			else if constexpr (size == 64) int64_t value;

			// TODO: Check if this way is fast enough
			std::istringstream buffer(*this);
			buffer >> value;

			// TODO: Check for end of string

			return value;
		}*/

		// Another option:
		// int16_t i;
		// std::sscanf(s, "%"SCNd16, &i);
		// !!! It parses ‘10qwerty’ without an exception!

		explicit inline operator int()           { return std::stoi (*this); }
		explicit inline operator long()          { return std::stol (*this); }
		explicit inline operator long long()     { return std::stoll(*this); }
		explicit inline operator unsigned long() { return std::stol (*this); }
		explicit inline operator unsigned long long()
		                                         { return std::stoll(*this); }
		explicit inline operator float()         { return std::stof (*this); }
		explicit inline operator double()        { return std::stod (*this); }
		explicit inline operator long double()   { return std::stold(*this); }
	};
}

#endif
