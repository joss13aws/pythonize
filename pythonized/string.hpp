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

		explicit inline operator float()         { return std::stof (*this); }
		explicit inline operator double()        { return std::stod (*this); }
		explicit inline operator long double()   { return std::stold(*this); }
	};
}

#endif
