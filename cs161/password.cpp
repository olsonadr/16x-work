#include <iostream>
#include <list>
#include <ctime>

/*
**  Program:	   Lab 3 - Password Generator
**  Author:		   Nick Olson
**  Date:		   12/28/2018
**  Description:   Generates a random password based on a users specifications.
*/

int main()
{
	srand(time(NULL));
	std::string lower [26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
							  "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
							 };
	std::string upper [26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
							  "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
							 };
	int length, count_lower, count_upper, count_numbers;
	std::string password = "";
	int random_num;
	bool keep_going = true;
	std::cout << std::endl << "Welcome to the password generator!" << std::endl <<
			  std::endl;

	while (keep_going)
	{
		std::cout << "How long should your password be? (length > 0)" << std::endl;
		std::cin >> length;
		std::cout << std::endl << "How many characters should be lowercase letters?" <<
				  std::endl;
		std::cin >> count_lower;
		std::cout << std::endl << "How many characters should be uppercase letters?" <<
				  std::endl;
		std::cin >> count_upper;
		std::cout << std::endl << "How many characters should be numbers?" << std::endl;
		std::cin >> count_numbers;

		if (count_lower + count_upper + count_numbers == length && length > 0)
		{
			std::cout << std::endl << "All valid inputs!" << std::endl << std::endl;
			keep_going = false;
		}
		else
		{
			std::cout << std::endl <<
					  "Either length invalid, or the components don't add to length of the password. Try again!"
					  << std::endl << std::endl;
		}
	}

	std::cout << "Generating password... ";

	for (int i = 0; i < length; i++)
	{
		// Choose which type to use for the place
		keep_going = true;

		while (keep_going)
		{
			random_num = rand();

			if (random_num % 3 == 0 && count_lower > 0)
			{
				password = password + lower[random_num % 26];
				count_lower--;
				keep_going = false;
			}
			else if (random_num % 3 == 1 && count_upper > 0)
			{
				password = password + upper[random_num % 26];
				count_upper--;
				keep_going = false;
			}
			else if (random_num % 3 == 2 && count_numbers > 0)
			{
				password = password + std::to_string(random_num % 10);
				count_numbers--;
				keep_going = false;
			}
		}
	}

	std::cout << "Done!" << std::endl << std::endl << "Your generated password is: "
			  << password <<
			  std::endl << std::endl;
	return 0;
}
