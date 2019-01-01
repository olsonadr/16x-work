#ifndef HELP_H
#define HELP_H
#include <iostream>
namespace HelperLib
{
	std::string input(std::string, int);
	bool isInt(std::string);
	bool isFloat(std::string);
	bool isEven(int);
	bool isOdd(int);
	bool equalsF(float, float, float);
	bool contains(std::string, std::string);
	std::string toUpper(std::string);
	std::string toLower(std::string);
	int getIntInput(std::string, int);
	float getFloatInput(std::string, int);

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
