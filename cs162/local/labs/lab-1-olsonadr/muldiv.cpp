#include "muldiv.hpp"

void print_tables(
    struct muldiv_entry ** table,
    int n)
{
	// Multiplication Table
	std::cout << std::endl
			  << "Multiplication Table:"
			  << std::endl
			  << " ";

	for (int k = 0; k < (n * 7 + 2); k++)
	{
		std::cout << "-";
	}

	std::cout << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << "|";

		for (int j = 0; j < n; j++)
		{
			std::cout << "| ";

			for (int k = 4; k > int(std::to_string(table[i][j].mul).length()); k--)
			{
				std::cout << " ";
			}

			std::cout << table[i][j].mul
					  << " ";
		}

		std::cout << " ||"
				  << std::endl
				  << " ";

		for (int k = 0; k < (n * 7 + 2); k++)
		{
			std::cout << "-";
		}

		std::cout << std::endl;
	}

	// Division Table
	std::cout << std::endl
			  << "Division Table:"
			  << std::endl
			  << " ";

	for (int k = 0; k < (n * 7 + 2); k++)
	{
		std::cout << "-";
	}

	std::cout << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << "|";

		for (int j = 0; j < n; j++)
		{
			std::cout << std::fixed
					  << std::setprecision(2)
					  << "| "
					  << table[i][j].div
					  << " ";
		}

		std::cout << " ||"
				  << std::endl
				  << " ";

		for (int k = 0; k < (n * 7 + 2); k++)
		{
			std::cout << "-";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}


struct muldiv_entry ** generate_tables(int n)
{
	struct muldiv_entry ** table = new struct muldiv_entry*[n];

	for (int i = 0; i < n; i++)
	{
		table[i] = new struct muldiv_entry[n];

		for (int j = 0; j < n; j++)
		{
			table[i][j] =
			{
				.mul = (i + 1) * (j + 1),
				.div = (float(i) + 1) / (float(j) + 1)
			};
		}
	}

	return table;
}


void free_tables(struct muldiv_entry ** table, int n)
{
	for (int index = 0; index < n; index++)
	{
		delete table[index];
	}

	delete[] table;
}
