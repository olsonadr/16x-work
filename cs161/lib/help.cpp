#include "help.h"
#include <iostream>
#include <sstream>

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

bool HelperLib::isInt(std::string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!(isdigit(input[i])))
		{
			return false;
		}
	}

	return true;
}

bool HelperLib::isFloat(std::string input)
{
	int count = 0;

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '.')
		{
			count++;
		}

		if (!(input[i] == '.' || isdigit(input[i])) || count > 1)
		{
			return false;
		}
	}

	return true;
}

bool HelperLib::isEven(int num)
{
	if (num % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HelperLib::isOdd(int num)
{
	if (num % 2 == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HelperLib::equalsF(float num1, float num2, float precision)
{
	float difference = num1 - num2;

	if (difference <= precision && difference >= -1 * precision)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HelperLib::contains(std::string sentence, std::string substring)
{
	bool flag;

	for (int outer = 0; outer < sentence.length() - substring.length(); outer++)
	{
		if (sentence[outer] == substring[0])
		{
			flag = true;

			for (int inner = 1; inner < substring.length(); inner++)
			{
				if (sentence[outer + inner] != substring[inner])
				{
					flag = false;
				}

				if (flag)
				{
					return true;
				}
			}
		}
	}

	return false;
}

std::string HelperLib::toUpper(std::string input)
{
	std::string upper = input;

	for (int i = 0; i < input.length(); i++)
	{
		if (islower(input[i]))
		{
			upper[i] = input[i] - 32;
		}
	}

	return upper;
}

std::string HelperLib::toLower(std::string input)
{
	std::string lower = input;

	for (int i = 0; i < input.length(); i++)
	{
		if (isupper(input[i]))
		{
			lower[i] = input[i] + 32;
		}
	}

	return lower;
}

int HelperLib::getIntInput(std::string prompt, int indentation_level)
{
	bool keepGoing = true;

	while (keepGoing)
	{
		std::string input = HelperLib::input(prompt, indentation_level);

		if (!HelperLib::isInt(input))
		{
			std::cout << "**ERROR! Input was not valid integer!**" << std::endl;
		}
		else
		{
			keepGoing = false;
			int input_int = 0;
			std::stringstream input_stream;
			input_stream << input;
			input_stream >> input_int;
			return input_int;
		}
	}

	return 0;
}

float HelperLib::getFloatInput(std::string prompt, int indentation_level)
{
	bool keepGoing = true;

	while (keepGoing)
	{
		std::string input = HelperLib::input(prompt, indentation_level);

		if (!HelperLib::isFloat(input))
		{
			std::cout << "**ERROR! Input was not valid integer!**" << std::endl;
		}
		else
		{
			keepGoing = false;
			float input_float = 0.0;
			std::stringstream input_stream;
			input_stream << input;
			input_stream >> input_float;
			return input_float;
		}
	}

	return 0.0;
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
