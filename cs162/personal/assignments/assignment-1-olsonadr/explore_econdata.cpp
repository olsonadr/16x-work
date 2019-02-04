/*
**  Program:		explore_econdata.cpp - Economic data viewer interface file.
**  Author:		Nick Olson
**  Date:		01/07/2019
**  Description:	This is the main file of the econdata program, which reads a economic
**			data file specified by the user through a command-line argument for
**			this files main method. The user is then presented multiple tools to
**			manipulate and interpret the data.
*/

#include "econdata.hpp"

/*
**  Function:		main
**  Description:	Calls functions to initialize values, read the
**			    data file, and give the user access to the
			    manipulation tools for the data.
**  Parameters:		int argc:
**			    Count of arguments passed on program-
**			    execution. Holds 1 for no additional
**			    arguments, 2+ otherwise.
**			char * argv[]:
**			    Array of the C-style strings representing
**			    all arguments passed on execution of the
**			    program. argv[0] is the name of the file.
**  Return Value:	Returns 0 on succesful program execution,
**			    1 for an argument error, 2 for a file
**			    read error, 3 for number of states read
**			    error, etc.
**  Pre-Conditions:	If an argument is provided, it points to an
**			    appropriately formatted data file.
**  Post-Conditions:	User is extremely satisfied with the quality
**			    of the program and my abilities.
*/
int main(int argc, char * argv[])
{
	// Vars
	int num_states = 0, error = 0;
	// Open file
	std::ifstream data_file;
	error = open_file(argc, argv, data_file);

	if (error > 0)
	{
		return error;
	}

	// Populate states
	num_states = get_num_states(data_file);

	if (num_states < 0)
	{
		return 3;
	}

	struct state * state_list = allocate_states(num_states);

	read_state_data(state_list, num_states, data_file);

	// Launch menu
	menu_system(state_list, num_states);

	// Cleanup
	free_state_data(state_list, num_states);

	data_file.close();

	return 0;
}
