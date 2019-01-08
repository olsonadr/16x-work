#include "muldiv.hpp"

int main(int argc, char * argv[])
{
	// Parsing Argument
	if (argc <= 1)
	{
		std::cout << "Hey stop, you gotta put an integer argument on that bad boy."
				  << std::endl;
		return 1;
	}

	int n = std::atoi(argv[1]);

	if (n <= 0)
	{
		std::cout << "Not a valid integer argument, nerd (>=1). Try again."
				  << std::endl;
		return 2;
	}

	// Create + Populate Table
	struct muldiv_entry ** table = generate_tables(n);
	// Print Table
	print_tables(table, n);
	// Cleanup
	free_tables(table, n);
}
