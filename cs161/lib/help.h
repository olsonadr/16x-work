#ifndef HELP_H
#define HELP_H
#include <iostream>
namespace HelperLib
{
	std::string input(std::string, int);
	
	template <typename Head>
	void print(const Head & first)
	{
		std::cout << first << std::endl;
	}
	
	template <typename Head, typename... Tail>
	void print(const Head & first, const Tail & ... args)
	{
		std::cout << first << " ";
		print(args...);
	}
}
#endif
