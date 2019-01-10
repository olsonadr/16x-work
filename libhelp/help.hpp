#ifndef HELP_H
#define HELP_H
#include <iostream>
#include <fstream>

namespace HelperLib
{
	std::string input(std::string, int indentation_level = 0);
	bool isInt(std::string);
	bool isFloat(std::string);
	bool isEven(int);
	bool isOdd(int);
	bool floatsEqual(float, float, float);
	bool contains(std::string, std::string);
	std::string toUpper(std::string);
	std::string toLower(std::string);
	int getIntInput(std::string, int indentation_level = 0);
	int getIntInputInRange(std::string, int start, int end, int indentation_level = 0);
	std::string getIntInputAsString(std::string, int indentation_level = 0);
	float getFloatInput(std::string, int indentation_level = 0);
	int displayMenu(std::string);

	// Prints the final argument and sends std::endl:
	template <typename Head>
	void print(const Head & first)
	{
		std::cout << first << std::endl;
	}
	// Prints the first argument of the function to cout
	// 		and recursively prints the remaining arguments.
	template <typename Head, typename... Tail>
	void print(const Head & first, const Tail & ... args)
	{
		std::cout << first << " ";
		print(args...);
	}
}
#endif
