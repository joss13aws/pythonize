#ifndef PYTHONIZE_STR
#define PYTHONIZE_STR

#include <string>

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

		class split;
		str join();

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
