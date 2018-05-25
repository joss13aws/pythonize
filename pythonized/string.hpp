#ifndef PYTHONIZE_STR
#define PYTHONIZE_STR

#include <string>
#include <type_traits>

namespace pythonize
{
	class str : public std::string
	{
		template <typename T>
		constexpr auto stringify(T arg)
		{
			if constexpr (std::is_arithmetic<T>::value)
				return std::to_string(arg);

			else return arg;
		}

	public:
		template <typename T, typename... Args>
		constexpr str(T first, Args... args)
			: std::string(stringify(first), args...) {}

		class split; // TODO
		str join(/* Many args or a list? */); // TODO

		explicit inline operator       float() { return std::stof (*this); }
		explicit inline operator      double() { return std::stod (*this); }
		explicit inline operator long double() { return std::stold(*this); }
	};
}

#endif
