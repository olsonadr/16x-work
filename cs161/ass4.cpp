#include <iostream>
#include <cmath>
#include "./lib/help.h"
#include <vector>
#include <map>
#include "../boost/boost/algorithm/string.hpp"
using namespace HelperLib;

float add(float num_1, float num_2)
{
	return num_1 + num_2;
}

float subtract(float num_1, float num_2)
{
	return num_1 - num_2;
}

float multiply(float num_1, float num_2)
{
	return num_1 * num_2;
}

float divide(float num_1, float num_2)
{
	return  num_1 / num_2;
}

float power(float num_1, float num_2)
{
	return std::pow(num_1, num_2);
}

void programmer_mode()
{
	int counter;
	print("\n\nProgrammer Mode:\n----------------");

	while (true)
	{
		float base_of_input = -1, desired_base = -1, temp_num = -1, input_num = -1;
		float result_num = 0, mid_step = 0;

		while (input_num < 0 or input_num != int(input_num))
		{
			input_num = getIntInput("\n  Positive integer to convert:");
			temp_num = input_num;

			if (input_num < 0)
			{
				print("\n    I said a *positive* integer.");
				print("    Please try again, nerd...");
			}
		}

		while (base_of_input < 2 or base_of_input > 10)
		{
			base_of_input =
				getIntInput("\n  Base of inputted number, 2 to 10:\n2 for binary, 10 for decimal, etc.)");

			if (base_of_input < 2 or base_of_input > 10)
			{
				print("\n    I said the base must be *2-10*.");
				print("    Please try again, nerd...");
			}
		}

		while (desired_base < 2 or desired_base > 10)
		{
			desired_base = getIntInput("\n  Desired base for conversion, 2 to 10:");

			if (desired_base < 2 or desired_base > 10)
			{
				print("\n    Can you follow instructions?");
				print("    *2 to 10*. Try again, nerd...");
			}
			else if (desired_base == base_of_input)
			{
				print("\n    I could let you waste our time with this,");
				print("    but I\"d rather let you try again...");
				desired_base = 0;
			}
		}

		counter = 0;

		while (temp_num > 0)
		{
			mid_step += std::pow(base_of_input, counter) * (int(temp_num) % 10) ;
			temp_num /= int(10);
			counter += 1;
		}

		std::vector<float> result_list = {};

		while (mid_step > 0)
		{
			result_list.push_back(int(mid_step) % int(desired_base));
			mid_step /= int(desired_base);
		}

		for (int counter = 0; counter < result_list.size(); counter++)
		{
			result_num += std::pow(10, counter) * result_list[counter];
		}

		print("\n  Result:",   "\n   ", input_num, "==>", result_num);
		print("    base -", base_of_input, "==> base -", desired_base);

		while (true)
		{
			print("\n  Do another conversion? (\"Y\" or \"N\"):");
			std::string user_input = input("    >>");

			if (toUpper(user_input) == "N")
			{
				return;
			}
			else if (toUpper(user_input) == "Y")
			{
				break;
			}
			else
			{
				print("\n    Are you doing this on purpose?");
				print("    Seriously? Please try again...\n");
			}
		}
	}

	print("\n\nConversions complete. Returning to menu...");
	print("------------------------------------------");
}


void scientific_mode()
{
	float curr_result = 0;
	std::string line = "";
	std::vector<std::string> line_list;
	std::string operand_1 = "";
	std::string operand_2 = "";

	legal_operators = {
		"+": add,
		"-": subtract,
		"*": multiply,
		"/": divide,
		"**": power
	}
	legal_operands = {
		"": curr_result,
		"ans": curr_result
	}

	print("\n\nScientific Mode:\n----------------\n");
	print("  Rules:\n  ------");
	print("    Limit to two operands and one operator per step.");
	print("    YOU MUST USE SPACES BETWEEN EVERY ELEMENT!");
	print("      Examples: \'5 + 5\' or \'9 ** 6\'.\n");
	print("    You may begin line a space and operator to operate on the last result as first operand.");
	print("    You may also use the keyword \'ans\' (lowercase) to represent the prior answer.");
	print("      Examples: \' + 8\' or \'5 ** ans\'.\n");
	print("    Operands can be integers, floating point numbers, or the str \'ans\' but not any other type.\n");
	print("    Operators can be \'+\', \'-\', \'*\', \'/\', or \'**\', but nothing else.\n");
	print("    To stop executing these operations, input \"exit\" with no characters before the word.\n");
	print("    Lastly, this calculator does not handle order of operations or multiple operators, so don\'t try.\n\n");

	print("  Operations:\n  -----------");

	while (true){
		legal_operands = {
			"": curr_result,
			"ans": curr_result
		}

		line = input("    >>");

		if (line == "exit"){
			break;}

		boost::split(line_list, line, [](char c){return c == ' ';});

		try{
			operand_1 = float(line_list[0]);
		}
		catch (std::exception e){
			try{
				operand_1 = legal_operands[line_list[0]];
			}
			except (std::exception e){
				print("\n    Invalid first operand or syntax!");
				print("    Follow the rules. Try again...\n");
				continue;}
			pass;
		}
		try:
			operand_2 = float(line_list[2]);
			pass;
		except:
			try:
				operand_2 = legal_operands[line_list[2]];
				pass;
			except:
				print("\n    Invalid second operand or syntax!");
				print("    Follow the rules. Try again...\n");
				continue;
			pass;
		
		# Do operation and print new curr_result:;
		try:
			curr_result = legal_operators[line_list[1]](operand_1, operand_2);
			pass;
		except:
			print("\n    Invalid operator or syntax!");
			print("    Follow the rules. Try again...\n");
			continue;
		
		# Displays curr_result without decimal if it is not needed:;
		if curr_result == int(curr_result):
			print("                                ", str(int(curr_result)),"\n");
		else:;
			print("                                ", str(curr_result),"\n");
	}
	print("\n\nOperations complete. Returning to menu...");
	print("-----------------------------------------");
;
