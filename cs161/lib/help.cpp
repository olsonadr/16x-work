#include "help.h"
#include <iostream>

std::string HelperLib::input(std::string prompt, int indentation_level = 0)
{
	std::string result;
	std::string indent = "";

	for (int i = 0; i < indentation_level; i++)
	{
		indent += "  ";
	}

	if (prompt[prompt.length() - 1] == ' ')
	{
		std::cout << indent << prompt;
	}
	else
	{
		std::cout << indent << prompt << std::endl << indent << ">> ";
	}

	std::getline(std::cin, result);
	return result;
}

/*
 *template <typename Head>
 *void HelperLib::print(const Head & first)
 *{
 *    std::cout << first << std::endl;
 *}
 *
 *template <typename Head, typename... Tail>
 *void HelperLib::print(const Head & first, const Tail & ... args)
 *{
 *    std::cout << first;
 *    print(args...);
 *}
 */
