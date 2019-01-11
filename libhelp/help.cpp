/*
**  Program:	   help.cpp - Helper Library
**  Author:	   Nick Olson
**  Date:	   12/26/2018
**  Description:   Runs and prints/returns the results of various functions.
*/


#include "help.hpp"
#include <iostream>
#include <sstream>


/*
** Function:		HelperLib::input
** Description:		Prompts the user for input using cout at a given
**				indentation level, using 2 spaces as an indent,
**			    and takes user input from cin as a string,
**			    accepting anything.
** Parameters		std::string prompt:
**			    The desired prompt for the user. If the prompt
**			    ends in a space, the cin occurs at the end of
**			    that terminal line, else, the cin takes place
**			    on the next line after a ">> " marker.
**			int indentation_level:
**			    The desired level of indentation for the prompt
**			    and cin call. For example, indentation_level = 1
**			    would result in a prompt of "  <prompt-value>".
** Returns:		The users input response as a std::string object.
** Pre-Conditions:	indentation_level >= 1.
*/
std::string HelperLib::input(std::string prompt, int indentation_level)
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
** Function:		HelperLib::isInt
** Description:		Checks if a given std::string is a valid integer.
** Parameters		std::string input:
**			    The std::string to be checked.
** Returns:		Whether the input can represent a valid integer
**			    (and so can be cast to int) as a bool.
**			    true --> input is an int, false --> it isn't.
*/
bool HelperLib::isInt(std::string input)
{
	for (int i = 0; i < int(input.length()); i++)
	{
		if (!(isdigit(input[i])))
		{
			return false;
		}
	}

	return true;
}


/*
** Function:		HelperLib::isFloat
** Description:		Checks if a given std::string is a valid float.
** Parameters		std::string input:
**			    The std::string to be checked.
** Returns:		Whether the input can represent a valid float
**			    (and so can be cast to float) as a bool.
**			    true --> input is a float, false --> it isn't.
*/
bool HelperLib::isFloat(std::string input)
{
	int count = 0;

	for (int i = 0; i < int(input.length()); i++)
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


/*
** Function:		HelperLib::isEven
** Description:		Checks if a given int is an even value or not.
** Parameters:		int num:
**			    The integer to be checked.
** Returns:		Whether the value of num is an even number as
**			    a bool value (true --> it is, false --> nope).
*/
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


/*
** Function:		HelperLib::isOdd
** Description:		Checks if a given int is an odd value or not.
** Parameters:		int num:
**			    The integer to be checked.
** Returns:		Whether the value of num is an odd number as
**			    a bool value (true --> it is, false --> nope).
*/
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


/*
** Function:		HelperLib::floatsEqual
** Description:		Checks if two float values are "equal" to eachother,
**			    meaning they are within some level of precision
**			    of eachother (to avoid errors in using ==).
** Parameters:		float num1:
**			    The first float value of the "equality".
**			float num2:
**			    The second float value of the "equality".
**			float precision:
**			    The level of precision represented as the max
**			    difference the values may have to be "equal".
** Returns:		Whether num1 and num2 are withing the value of
**			    precision of eachother (or "equal").
** Pre-Conditions:	precision >= 0.
*/
bool HelperLib::floatsEqual(float num1, float num2, float precision)
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


/*
** Function:		HelperLib::contains
** Description:		Checks whether a given string contains a given
**			    substring fully at any point in its length.
** Parameters		std::string sentence:
**			    The full string in which the method searches.
**			std::string substring:
**			    The substring the method searches for.
** Returns:		Whether the complete substring was found within
**			    sentence, as a bool value.
*/
bool HelperLib::contains(std::string sentence, std::string substring)
{
	bool flag = false;

	for (int outer = 0; outer < int(sentence.length()) - int(substring.length()); outer++)
	{
		if (sentence[outer] == substring[0])
		{
			flag = true;

			for (int inner = 1; inner < int(substring.length()); inner++)
			{
				if (sentence[outer + inner] != substring[inner])
				{
					return false;
				}
			}
		}
	}

	return flag;
}


/*
** Function:		HelperLib::toUpper
** Description:		Returns a copy of a given std::string where every
**			    possible char is uppercase.
** Parameters		std::string input:
**			    The std::string to be modified.
** Returns:		A copy of the string (does not modify the original)
**			    where every lowercase alphabetical character is
**			    changed to its uppercase equivelant.
** Post-Conditions:	input is unmodified.
*/
std::string HelperLib::toUpper(std::string input)
{
	std::string upper = input;

	for (int i = 0; i < int(input.length()); i++)
	{
		if (islower(input[i]))
		{
			upper[i] = input[i] - 32;
		}
	}

	return upper;
}


/*
** Function:		HelperLib::toLower
** Description:		Returns a copy of a given std::string where every
**			    possible char is lowercase.
** Parameters		std::string input:
**			    The std::string to be modified.
** Returns:		A copy of the string (does not modify the original)
**			    where every uppercase alphabetical character is
**			    changed to its lowercase equivelant.
** Post-Conditions:	input is unmodified.
*/
std::string HelperLib::toLower(std::string input)
{
	std::string lower = input;

	for (int i = 0; i < int(input.length()); i++)
	{
		if (isupper(input[i]))
		{
			lower[i] = input[i] + 32;
		}
	}

	return lower;
}


/*
** Function:		HelperLib::getIntInput
** Description:		Prompts the user for input using cout at a given
**			    indentation level, using 2 spaces as an indent,
**			    and takes user input from cin as a string,
**			    accepting only valid integer inputs, converting
**			    the input to an integer before returning.
** Parameters		std::string prompt:
**			    The desired prompt for the user. If the prompt
**			    ends in a space, the cin occurs at the end of
**			    that terminal line, else, the cin takes place
**			    on the next line after a ">> " marker.
**			int indentation_level:
**			    The desired level of indentation for the prompt
**			    and cin call. For example, indentation_level = 1
**			    would result in a prompt of "  <prompt-value>".
** Returns:		The users input response as a int value, 0 if the
**			    execution failed at some point.
** Pre-Conditions:	indentation_level >= 1.
*/
int HelperLib::getIntInput(std::string prompt, int indentation_level)
{
	bool keepGoing = true;
	int input_int = 0;

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
			std::stringstream input_stream;
			input_stream << input;
			input_stream >> input_int;
			return input_int;
		}
	}

	return input_int;
}


/*
** Function:		HelperLib::getIntInputInRange
** Description:		Prompts the user for input using cout at a given
**			    indentation level, using 2 spaces as an indent,
**			    and takes user input from cin as a string,
**			    accepting only valid integer inputs, converting
**			    the input to an integer iff the input is also
**			    within the range given (inclusive)
** Parameters		std::string prompt:
**			    The desired prompt for the user. If the prompt
**			    ends in a space, the cin occurs at the end of
**			    that terminal line, else, the cin takes place
**			    on the next line after a ">> " marker.
**			int start:
**			    The starting value of the range of valid inputs.
**			int end:
**			    The ending value of the range of valid inputs.
**			int indentation_level:
**			    The desired level of indentation for the prompt
**			    and cin call. For example, indentation_level = 1
**			    would result in a prompt of "  <prompt-value>".
** Returns:		The users input response as a int value, 0 if the
**			    execution failed at some point.
** Pre-Conditions:	indentation_level >= 1, start <= end.
*/
int HelperLib::getIntInputInRange(std::string prompt, int start, int end,
                                  int indentation_level)
{
	bool keepGoing = true;
	int input_int = 0;

	while (keepGoing)
	{
		input_int = HelperLib::getIntInput(prompt, indentation_level);

		if (input_int >= start && input_int <= end)
		{
			keepGoing = false;
			return input_int;
		}
		else
		{
			std::cout << "**ERROR! Input is not in range [" << start << "-" << end << "]!**" <<
				  std::endl;
		}
	}

	return input_int;
}


/*
** Function:		HelperLib::getIntInputAsString
** Description:		Prompts the user for input using cout at a given
**			    indentation level, using 2 spaces as an indent,
**			    and takes user input from cin as a string,
**			    accepting only valid integer inputs.
** Parameters		std::string prompt:
**			    The desired prompt for the user. If the prompt
**			    ends in a space, the cin occurs at the end of
**			    that terminal line, else, the cin takes place
**			    on the next line after a ">> " marker.
**			int indentation_level:
**			    The desired level of indentation for the prompt
**			    and cin call. For example, indentation_level = 1
**			    would result in a prompt of "  <prompt-value>".
** Returns:		The users input response as a string value, 0 if the
**			    execution failed at some point.
** Pre-Conditions:	indentation_level >= 1.
*/
std::string HelperLib::getIntInputAsString(std::string prompt, int indentation_level)
{
	bool keepGoing = true;
	std::string input = "";

	while (keepGoing)
	{
		input = HelperLib::input(prompt, indentation_level);

		if (!HelperLib::isInt(input))
		{
			std::cout << "**ERROR! Input was not valid integer!**" << std::endl;
		}
		else
		{
			keepGoing = false;
			return input;
		}
	}

	return input;
}


/*
** Function:		HelperLib::getIntInput
** Description:		Prompts the user for input using cout at a given
**			    indentation level, using 2 spaces as an indent,
**			    and takes user input from cin as a string,
**			    accepting only valid float inputs, converting
**			    the input to a float before returning.
** Parameters		std::string prompt:
**			    The desired prompt for the user. If the prompt
**			    ends in a space, the cin occurs at the end of
**			    that terminal line, else, the cin takes place
**			    on the next line after a ">> " marker.
**			int indentation_level:
**			    The desired level of indentation for the prompt
**			    and cin call. For example, indentation_level = 1
**			    would result in a prompt of "  <prompt-value>".
** Returns:		The users input response as a float value, 0 if the
**			    execution failed at some point.
** Pre-Conditions:	indentation_level >= 1.
*/
float HelperLib::getFloatInput(std::string prompt, int indentation_level)
{
	bool keepGoing = true;

	while (keepGoing)
	{
		std::string input = HelperLib::input(prompt, indentation_level);

		if (!HelperLib::isFloat(input))
		{
			std::cout << "**ERROR! Input was not valid float!**" << std::endl;
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

// The following two functions are commented out becasue they are
//  nonfunctional and I don't want to work on them more right now.
/*
** Function:		displayMenu
** Description:		Displays a menu read from a file at path at
**			    the path in the passed std::string.
** Parameters:		std::string path_to_file:
**			    Path to the menu file.
**			int starting_line:
**			    The line in the file on which to start
**			    the menu display. Allows for menu to be
**			    launched from a submenu.
** Return Value:	Returns users selection as line their choice
**			is on, -1 for a file read error, etc.
** Example file:	"Main menu:" 3
**			"(0) Option 1" 0
**			"(1) Option 2" 1
**			"(2) Sub Menu" 2
**			"(3) Suboption 1" 0
**			"(4) Suboption 2" 0
**			"(5) Option 3" 0
*/
/*
int HelperLib::menuSystem(std::string path_to_file, int starting_line = 0)
{
	// Open File
	std::ifstream data_file;
	data_file.open(path);

	if (data_file.fail())
	{
		std::cout << "**ERROR! Invalid path to file provided.**"
			  << std::endl;
		return -1;
	}
	else if (!data_file.is_open())
	{
		std::cout << "**ERROR! File reading error, try again.**"
			  << std::endl;
		return -1;
	}

	// Menu Parsing
	int result = displayMenu(data_file);

	// Cleanup
	data_file.close();
}
*/

/*
** Function:		displayMenu
** Description:		Displays a specific menu's header and list of
**			    options, returning the user's choice.
** Parameters:		std::ifstream data_file:
**			    The datafile to read from
** Return Value:	The integer line number of the users choice
**			    relative to the current menu.
** Pre-Conditions:	The ifstream is at the beginning of the line
**			    with the menu's header tag and number of
**			    options within.
** Post-Conditions:	
** Example file:	"Main menu:" 3
**			"(0) Option 1" 0
**			"(1) Option 2" 1
**			"(2) Sub Menu" 2
**			"(3) Suboption 1" 0
**			"(4) Suboption 2" 0
**			"(5) Option 3" 0
*/
/*
int HelperLib::displayMenu(std::ifstream data_file)
{
    int result = 0;
    std::cout << "#=~" << std::endl;
*/
    





    std::cout << "#=~" << std::endl;
}


// This commented code is the code for my print method, which is defined in
//	the associated header file "help.h" that should be in this dir.
/*
** template <typename Head>
** void HelperLib::print(const Head & first)
** {
** std::cout << first << std::endl;
** }
**
** template <typename Head, typename... Tail>
** void HelperLib::print(const Head & first, const Tail & ... args)
** {
** std::cout << first;
** print(args...);
** }
*/
