/*
**  Program:	   econdata.cpp - Economic data viewer function implementations.
**  Author:		   Nick Olson
**  Date:		   01/07/2019
**  Description:   This program implements functions that read data from a user-provided
**				   data file that is passed from a command-line argument, and gives the
**				   user tools to interpret the data.
*/


#include "econdata.hpp"


/*
**  Function:			open_file
**  Description:		Opens the file the user specified in their command-
**							argument. Returns error codes otherwise.
**  Parameters:			int argc:
**							Number of arguments passed.
**						char * argv[]:
**							Array of arguments passed, starting with program
**							filename at argv[0].
**						std::ifstream data_file:
**							The ifstream to open the file into.
**  Return Value:       Returns 0 for successful execution, 1 for argument
**							error, 2 for a file read error, etc.
**  Pre-Conditions:
**  Post-Conditions:
*/
int open_file(
    int argc,
    char * argv[],
    std::ifstream & data_file)
{
	// Open File
	if (argc == 1)
	{
		std::cout << "**ERROR! No path to file provided.**" << std::endl;
		return 1;
	}

	data_file.open(argv[1]);

	if (data_file.fail())
	{
		std::cout << "**ERROR! Invalid path to file provided.**" << std::endl;
		return 1;
	}
	else if (!data_file.is_open())
	{
		std::cout << "**ERROR! File reading error, try again.**" << std::endl;
		return 2;
	}

	return 0;
}


/*
**  Function:			get_num_states
**  Description:		Gets the number of states contained in the data
**							file on the first line, returns it.
**  Parameters:			std::ifstream data_file:
**							The filestream the data is opened into.
**  Return Value:       Returns the number of states in the data file,
**							or -1 in the event of an error.
**  Pre-Conditions:     The data_file filestream is initialized and
**							the file is already open; file correct;
**							the stream has not been accessed yet.
**  Post-Conditions:    The filestream is onto the first state's line.
*/
int get_num_states(
    std::ifstream & data_file)
{
	int num_states = 0;
	data_file >> num_states;

	if (data_file.fail())
	{
		std::cout << "**ERROR! Failed to read number of states.**" << std::endl;
		return -1;
	}

	return num_states;
}


/*
**  Function:			allocate_states
**  Description:		Allocates an array of the passed number of states.
**  Parameters:			int num_states:
**							The number of states in the data file.
**  Return Value:       Returns an array of type struct state with length
**							of num_states.
**  Pre-Conditions:     num_states >= 0
*/
struct state * allocate_states(
    int num_states)
{
	return new struct state[num_states];
}


/*
**  Function:			read_state_data
**  Description:		Reads the data from the passed data_file fstream
**							into the passed passed state array. Leaving
**							the fstream at the end of the file.
**  Parameters:			struct state * state_list:
**							The list to populate with the states in the
**							filestream.
**						num_states:
**							The number of states in the filestream.
**						std::ifstream & data_file:
**							The filestream containing the contents of the
**							data file passed to the program.
**  Pre-Conditions:		num_states >= 0, data_file is at the line about
**							the first state.
**  Post-Conditions:	state_list is populated with all the states in
**							the data_file (and the counties for each state).
*/
void read_state_data(
    struct state * state_list,
    int num_states,
    std::ifstream & data_file)
{
	std::string name;
	float unemployed_2007, unemployed_2015;
	int med_income, num_counties;
	struct county * county_list;

	for (int index = 0; index < num_states; index++)
	{
		data_file >> name >> unemployed_2007
				  >> unemployed_2015 >> med_income
				  >> num_counties;
		county_list = allocate_counties(num_counties);
		state_list[index] =
		{
			.name = name,
			.unemployed_2007 = unemployed_2007,
			.unemployed_2015 = unemployed_2015,
			.med_income = med_income,
			.county_list = county_list,
			.num_counties = num_counties
		};
	}
}


/*
**  Function:			allocate_counties
**  Description:		Allocates an array of the passed number of counties.
**  Parameters:			int num_counties:
**							The number of counties in the data file.
**  Return Value:       Returns an array of type struct county with length
**							of num_counties.
**  Pre-Conditions:     num_counties >= 0
*/
struct county * allocate_counties(
    int num_counties)
{
	return new struct county[num_counties];
}


/*
**  Function:			read_county_data
**  Description:		Reads the data from the passed data_file fstream
**							into the passed passed county array. Leaving
**							the fstream at the next county's section or
**							the end of the file.
**  Parameters:			struct county * county_list:
**							The list to populate with the counties in the
**							filestream.
**						num_counties:
**							The number of counties in the filestream.
**						std::ifstream & data_file:
**							The filestream containing the contents of the
**							data file passed to the program.
**  Pre-Conditions:		num_counties >= 0, data_file is at the line about
**							the first county.
**  Post-Conditions:	county_list is populated with all the counties in
**							the given state.
*/
void read_county_data(
    struct county * county_list,
    int num_counties,
    std::ifstream & data_file)
{
	std::string name;
	float unemployed_2007, unemployed_2015;
	int med_income;

	for (int index = 0; index < num_counties; index++)
	{
		data_file >> name >> unemployed_2007
				  >> unemployed_2015 >> med_income;
		county_list[index] =
		{
			.name = name,
			.unemployed_2007 = unemployed_2007,
			.unemployed_2015 = unemployed_2015,
			.med_income = med_income
		};
	}
}


/*
**  Function:			free_state_data
**  Description:		Releases all data associated with the states and
**							subsequent counties contained within the given
**							state_list array.
**  Parameters:			struct state * state_list:
**							The array of states to be processed.
**						int num_states:
**							The number of states in the array.
**  Pre-Conditions:     state_list is not empty (if num_states > 0), while
**							num_states >= 0.
**  Post-Conditions:    All data related to the states in the passed array
**							or the counties contained within is released,
**							avoiding memory leaks.
*/
void free_state_data(
    struct state * state_list,
    int num_states)
{
	for (int index = 0; index < num_states; index++)
	{
		delete state_list[index].counties;
	}

	delete state_list;
}


/*
**  Function:			menu_system
**  Description:		System of menus that gets what the user would like
**							to do with the data to better view it, allows
**							the user to either exit or repeat operations.
**  Parameters:			struct state * state_list:
**							The list of states to be sorted through.
**						int num_states:
**							The number of states represented in the list.
**  Pre-Conditions:     state_list is not empty, all setup has been run.
*/
void menu_system(
    struct state * state_list,
    int num_states)
{}


/*
**  Function:			find_state
**  Description:		Returns the struct state with the highest/lowest of
**							a number of possible fields, all determined by
**							the parameters of the function.
**  Parameters:			struct state * state_list:
**							The list of states to be searched through.
**						int num_states:
**							The number of states in the state_list.
**						std::string search_type:
**							The type of search to be done (searching for the
**							"min" or the "max" of a given field).
**						std::string field_name:
**							The field to be considered in the search, can be
**							"med_income" or "unemployed_2015".
**  Return Value:       Returns the state found with the highest/lowest of
**							the requested type. Leaves all params unchanged.
**  Pre-Conditions:     state_list in non-empty, unless num_states is 0.
*/
struct state find_state(
    struct state * state_list,
    int num_states,
    std::string search_type,
    std::string field_name)
{}


/*
**  Function:			find_county
**  Description:		Returns the struct county with the highest/lowest of
**							a number of possible fields, all determined by
**							the parameters of the function.
**  Parameters:			struct county * county_list:
**							The list of counties to be searched through.
**						int num_counties:
**							The number of counties in the county_list.
**						std::string search_type:
**							The type of search to be done (searching for the
**							"min" or the "max" of a given field).
**						std::string field_name:
**							The field to be considered in the search, can be
**							"med_income" or "unemployed_2015".
**  Return Value:       Returns the county found with the highest/lowest of
**							the requested type. Leaves all params unchanged.
**  Pre-Conditions:     county_list in non-empty, unless num_counties is 0.
*/
struct county find_county(
    struct state state_to_expand,
    std::string search_type,
    std::string field_name)
{
	float min_or_max;
	for (int index = 0; index < state_to_expand.num_counties; index++) {
		
	}
}


/*
**  Function:			compare_state_employment
**  Description:		Returns whether the first state passed has a smaller
**							or more negative change in its unemployment from
**							2007 to 2015.
**  Parameters:			struct state first_state:
**							The first state to be compared.
**						struct state second_state:
**							The second state to be compared.
**  Return Value:       Returns whether the change in unemployment is less
**							in the first param than the second as a bool.
**  Pre-Conditions:     The states are both initialized fully.
*/
bool compare_state_employment(
    struct state first_state,
    struct state second_state)
{
	float first_diff, second_diff;
	first_diff = first_state.unemployed_2015-first_state.unemployed_2007;
	second_diff = second_state.unemployed_2015-second_state.unemployed_2007;
	return first_diff < second_diff;
}


/*
**  Function:			compare_state_income
**  Description:		Returns whether the first state passed has a lower
**							median income value than the second.
**  Parameters:			struct state first_state:
**							The first state to be compared.
**						struct state second_state:
**							The second state to be compared.
**  Return Value:       Returns whether the median income is less in the
**							first param than the second as a bool.
**  Pre-Conditions:     The states are both initialized fully.
*/
bool compare_state_income(
    struct state first_state,
    struct state second_state)
{
	return first_state.med_income < second_state.med_income;
}


/*
**  Function:			compare_county_employment
**  Description:		Returns whether the first county passed has a smaller
**							or more negative change in its unemployment from
**							2007 to 2015.
**  Parameters:			struct county first_county:
**							The first county to be compared.
**						struct county second_county:
**							The second county to be compared.
**  Return Value:       Returns whether the change in unemployment is less
**							in the first param than the second as a bool.
**  Pre-Conditions:     The counties are both initialized fully.
*/
bool compare_county_employment(
    struct county first_county,
    struct state second_county)
{
	float first_diff, second_diff;
	first_diff = first_county.unemployed_2015-first_county.unemployed_2007;
	second_diff = second_county.unemployed_2015-second_county.unemployed_2007;
	return first_diff < second_diff;
}


/*
**  Function:			compare_county_income
**  Description:		Returns whether the first county passed has a lower
**							median income value than the second.
**  Parameters:			struct county first_county:
**							The first county to be compared.
**						struct county second_county:
**							The second county to be compared.
**  Return Value:       Returns whether the median income is less in the
**							first param than the second as a bool.
**  Pre-Conditions:     The counties are both initialized fully.
*/
bool compare_county_income(
    struct county first_county,
    struct county second_county)
{
	return first_county.med_income < second_county.med_income;
}


/*
**  Function:			display_state_data
**  Description:		Prints all the stored data about a state to cout.
**  Parameters:			stuct state state_to_display:
**							The struct state to display.
**  Pre-Conditions:     The state is initialized fully.
*/
void display_state_data(
    struct state state_to_display)
{
	HelperLib::print("Data of ", state_to_display.name, "State:");
	HelperLib::print("Median Income:\n",
					 "  ", state_to_display.med_income, 1);
	HelperLib::print("Unemployment in 2007:\n",
					 "  ", state_to_display.unemployed_2007, 1);
	HelperLib::print("Unemployment in 2015:\n",
					 "  ", state_to_display.unemployed_2015, 1);
	HelperLib::print("Number of Counties:\n",
					 "  ", state_to_display.num_counties, 1);
	std::cout << "#=~"
			  << std::endl;
}


/*
**  Function:			display_county_data
**  Description:		Prints all the stored data about a county to cout.
**  Parameters:			stuct county county_to_display:
**							The struct county to display.
**  Pre-Conditions:     The county is initialized fully.
*/
void display_county_data(
    struct county county_to_display)
{
	HelperLib::print("Data of ", county_to_display.name, "County:");
	HelperLib::print("Median Income:\n",
					 "  ", county_to_display.med_income, 1);
	HelperLib::print("Unemployment in 2007:\n",
					 "  ", county_to_display.unemployed_2007, 1);
	HelperLib::print("Unemployment in 2015:\n",
					 "  ", county_to_display.unemployed_2015, 1);
	std::cout << "#=~"
			  << std::endl;
}


/*
**  Function:			search_for_state
**  Description:		Finds and returns the first state with the given
**							name found in the passed array of states.
**  Parameters:			struct state * state_list:
**							The list of states to search through.
**						int num_states:
**							The number of states referenced in state_list.
**						std::string search_key:
**							The keyword to search for in the state_list.
**  Return Value:       Returns the first struct state found in the given
**							state_list that contains the passed keyword.
**  Pre-Conditions:     state_list is not empty, the states are all fully
**							initialized with names.
*/
struct state search_for_state(
    struct state * state_list,
    int num_states,
    std::string search_key)
{
	for (int index = 0; index < num_states; index++)
	{
		if (HelperLib::contains(state_list[index].name, search_key))
		{
			return state_list[index];
		}
	}

	return state_list[0];
}


/*
**  Function:			search_for_county
**  Description:		Finds and returns the first county with the given
**							name found in the counties in the passed state.
**  Parameters:			struct state state_to_expand:
**							The state with the counties to search through.
**						std::string search_key:
**							The keyword to search for in the state_list.
**  Return Value:       Returns the first struct county found in the given
**							state's list that contains the passed keyword.
**  Pre-Conditions:     county_list is not empty, the counties are all fully
**							initialized with names, the state is initialized.
*/
struct county search_for_county(
    struct state state_to_expand,
    std::string search_key)
{
	for (int index = 0; index < state_to_expand.num_counties; index++)
	{
		if (HelperLib::contains(state_to_expand.county_list[index].name, search_key))
		{
			return state_to_expand.county_list[index];
		}
	}

	return state_to_expand.county_list[0];
}


/*
**  Function:			display_states
**  Description:		Prints all states in a given state_list to cout.
**  Parameters:			struct state * state_list:
**							The list of states to be displayed.
**						int num_states:
**							The number of states contain in state_list.
**  Pre-Conditions:     The state_list is not empty, unless num_states
**							is equal to 0, and all states contained are
**							fully initialized (at least names).
*/
void display_states(
    struct state * state_list,
    int num_states)
{
	std::cout << "States Loaded:"
			  << std::endl;

	for (int index = 0; index < num_states; index++)
	{
		std::cout << " ~"
				  << state_list[index].name
				  << std::endl;
	}

	std::cout << "#=~"
			  << std::endl;
}


/*
**  Function:			display_counties
**  Description:		Prints all counties in a given county_list to cout.
**  Parameters:			struct state state_to_expand:
**							The state containing the counties to display.
**  Pre-Conditions:     The county_list is not empty, unless num_counties
**							is equal to 0, and all counties contained are
**							fully initialized (at least names), state is
**							also initialized.
*/
void display_counties(
    struct state state_to_expand)
{
	std::cout << "Counties of "
			  << state_to_expand.name
			  << " State:"
			  << std::endl;

	for (int index = 0; index < state_to_expand.num_counties; index++)
	{
		std::cout << " ~"
				  << state_to_expand.county_list[index].name
				  << std::endl;
	}

	std::cout << "#=~"
			  << std::endl;
}
