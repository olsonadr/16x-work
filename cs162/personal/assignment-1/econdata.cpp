/*
**  Program:	   econdata.cpp - Economic data viewer function implementation file.
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
		data_file >> name
				  >> unemployed_2007
				  >> unemployed_2015
				  >> med_income
				  >> num_counties;
		county_list = allocate_counties(num_counties);
		read_county_data(
			county_list,
			num_counties,
			data_file
		);
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
		delete[] state_list[index].county_list;
	}

	delete[] state_list;
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
{
	int int_input;
	bool keep_going_main = true, keep_going_counties = true;
	bool is_sorted_med = false, is_sorted_employ = false;
	std::system("CLS");
	std::system("clear");

	while (keep_going_main)
	{
		std::cout << "Main Menu:"
				  << std::endl
				  << "  (0) List out all loaded states."
				  << std::endl
				  << "  (1) Find state with highest median income."
				  << std::endl
				  << "  (2) Find state with lowest median income."
				  << std::endl
				  << "  (3) Find state with highest unemployment in 2015."
				  << std::endl
				  << "  (4) Find state with lowest unemployment in 2015."
				  << std::endl
				  << "  (5) Sort states by median household income."
				  << std::endl
				  << "  (6) Sort states by change in unemployment from 2007 to 2015."
				  << std::endl
				  << "  (7) Search for a specific state to view."
				  << std::endl
				  << "  (8) Quit the program."
				  << std::endl
				  << "#=~"
				  << std::endl;
		int_input = HelperLib::getIntInputInRange("Number of your choice: ", 0, 8, 1);
		std::system("CLS");
		std::system("clear");
		std::cout << "#=~"
				  << std::endl;

		switch (int_input)
		{
			default: // Also int_input == 0
				display_states(
					state_list,
					num_states,
					1);
				break;

			case 1:
				display_state_data(
					find_state(
						state_list,
						num_states,
						"max",
						"med_income"
					), 1);
				break;

			case 2:
				display_state_data(
					find_state(
						state_list,
						num_states,
						"min",
						"med_income"
					), 1);
				break;

			case 3:
				display_state_data(
					find_state(
						state_list,
						num_states,
						"max",
						"unemployed_2015"
					),
					1);
				break;

			case 4:
				display_state_data(
					find_state(
						state_list,
						num_states,
						"min",
						"unemployed_2015"
					), 1);
				break;

			case 5:

				// Sort array using compare_state_income for comparisons, but only
				//	 if the array is not already most recently sorted in this way.
				if (!is_sorted_med)
				{
					std::sort(
						state_list,
						state_list + num_states,
						compare_state_income
					);
				}

				is_sorted_med = true;
				is_sorted_employ = false;
				display_states(
					state_list,
					num_states,
					1);
				break;

			case 6:

				// Sort array using compare_state_employment for comparisons, but only
				//	 if the array is not already most recently sorted in this way.
				if (!is_sorted_employ)
				{
					std::sort(
						state_list,
						state_list + num_states,
						compare_state_employment
					);
				}

				is_sorted_med = false;
				is_sorted_employ = true;
				display_states(
					state_list,
					num_states,
					1);
				break;

			case 8:
				keep_going_main = false;
				break;

			case 7:
				std::string keyword = HelperLib::input("Search: ", 1);
				struct state selected_state = search_for_state(
												  state_list,
												  num_states,
												  keyword
											  );
				std::cout << "#=~"
						  << std::endl;

				if (selected_state.name == "no_result")
				{
					std::cout << "    No state found! Try again!"
							  << std::endl;
				}
				else
				{
					std::cout << "  Found!"
							  << std::endl
							  << "#=~"
							  << std::endl;
					display_state_data(
						selected_state, 1
					);
					int_input = HelperLib::getIntInputInRange(
									"Explore this state's counties? (1, 0)", 0, 1, 1
								);
				}

				std::cout << "#=~"
						  << std::endl;

				if (int_input == 1)
				{
					keep_going_counties = true;

					while (keep_going_counties)
					{
						std::cout << "  "
								  << selected_state.name
								  << "'s Counties:"
								  << std::endl
								  << "    (0) List out all counties."
								  << std::endl
								  << "    (1) Find county with highest median income."
								  << std::endl
								  << "    (2) Find county with lowest median income."
								  << std::endl
								  << "    (3) Find county with highest unemployment in 2015."
								  << std::endl
								  << "    (4) Find county with lowest unemployment in 2015."
								  << std::endl
								  << "    (5) Sort counties by median household income (increasing)."
								  << std::endl
								  << "    (6) Sort counties by change in unemployment from 2007 to 2015 (negative to positive)."
								  << std::endl
								  << "    (7) Search for a specific county to view."
								  << std::endl
								  << "    (8) Quit back to main_menu."
								  << std::endl
								  << "#=~"
								  << std::endl;
						int_input = HelperLib::getIntInputInRange("Number of your choice: ", 0, 8, 1);
						std::system("CLS");
						std::system("clear");
						std::cout << "#=~"
								  << std::endl;

						switch (int_input)
						{
							default: // Also int_input == 0
								display_counties(
									selected_state,	2
								);
								break;

							case 1:
								display_county_data(
									find_county(
										selected_state,
										"max",
										"med_income"
									), 2);
								break;

							case 2:
								display_county_data(
									find_county(
										selected_state,
										"min",
										"med_income"
									), 2);
								break;

							case 3:
								display_county_data(
									find_county(
										selected_state,
										"min",
										"unemployed_2015"
									), 2);
								break;

							case 4:
								display_county_data(
									find_county(
										selected_state,
										"max",
										"unemployed_2015"
									), 2);
								break;

							case 5:

								// Sort array using compare_county_income for comparisons, but only
								//	 if the array is not already most recently sorted in this way.
								if (!is_sorted_med)
								{
									std::sort(
										selected_state.county_list,
										selected_state.county_list + selected_state.num_counties,
										compare_county_income
									);
								}

								is_sorted_med = true;
								is_sorted_employ = false;
								display_counties(
									selected_state, 2
								);
								break;

							case 6:

								// Sort array using compare_county_employment for comparisons, but only
								//	 if the array is not already most recently sorted in this way.
								if (!is_sorted_employ)
								{
									std::sort(
										selected_state.county_list,
										selected_state.county_list + selected_state.num_counties,
										compare_county_employment
									);
								}

								is_sorted_med = false;
								is_sorted_employ = true;
								display_counties(
									selected_state, 2
								);
								break;

							case 8:
								keep_going_counties = false;
								break;

							case 7:
								std::string keyword = HelperLib::input("Search: ", 2);
								struct county result = search_for_county(
														   selected_state,
														   keyword
													   );

								if (result.name == "no_result")
								{
									std::cout << "    No county found! Try again!"
											  << std::endl
											  << "#=~"
											  << std::endl;
								}
								else
								{
									std::cout << "    Found!"
											  << std::endl
											  << "#=~"
											  << std::endl;
									display_county_data(result, 2);
								}

								break;
						}
					}

					break;
				}
		}
	}
}


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
**  Pre-Conditions:     state_list in non-empty.
*/
struct state find_state(
    struct state * state_list,
    int num_states,
    std::string search_type,
    std::string field_name)
{
	float min_or_max;
	int stored_index = 0;

	if (field_name == "med_income")
	{
		min_or_max = state_list[0].med_income;
	}
	else // "unemployed_2015" was passed or invalid std::string was passed.
	{
		min_or_max = state_list[0].unemployed_2015;
	}

	for (int index = 1; index < num_states; index++)
	{
		if (field_name == "med_income")
		{
			if (search_type == "min")
			{
				if (state_list[index].med_income < state_list[stored_index].med_income)
				{
					min_or_max = state_list[index].med_income;
					stored_index = index;
				}
			}
			else
			{
				if (state_list[index].med_income > state_list[stored_index].med_income)
				{
					min_or_max = state_list[index].med_income;
					stored_index = index;
				}
			}
		}
		else
		{
			if (search_type == "min")
			{
				if (state_list[index].unemployed_2015 <
						state_list[stored_index].unemployed_2015)
				{
					min_or_max = state_list[index].unemployed_2015;
					stored_index = index;
				}
			}
			else
			{
				if (state_list[index].unemployed_2015 >
						state_list[stored_index].unemployed_2015)
				{
					min_or_max = state_list[index].unemployed_2015;
					stored_index = index;
				}
			}
		}
	}

	return state_list[stored_index];
}


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
	int stored_index = 0;
	struct county * c_list = state_to_expand.county_list;

	if (field_name == "med_income")
	{
		min_or_max = c_list[0].med_income;
	}
	else // "unemployed_2015" was passed or invalid std::string was passed.
	{
		min_or_max = c_list[0].unemployed_2015;
	}

	for (int index = 1; index < state_to_expand.num_counties; index++)
	{
		if (field_name == "med_income")
		{
			if (search_type == "min")
			{
				if (c_list[index].med_income < c_list[stored_index].med_income)
				{
					min_or_max = c_list[index].med_income;
					stored_index = index;
				}
			}
			else
			{
				if (c_list[index].med_income > c_list[stored_index].med_income)
				{
					min_or_max = c_list[index].med_income;
					stored_index = index;
				}
			}
		}
		else
		{
			if (search_type == "min")
			{
				if (c_list[index].unemployed_2015 < c_list[stored_index].unemployed_2015)
				{
					min_or_max = c_list[index].unemployed_2015;
					stored_index = index;
				}
			}
			else
			{
				if (c_list[index].unemployed_2015 > c_list[stored_index].unemployed_2015)
				{
					min_or_max = c_list[index].unemployed_2015;
					stored_index = index;
				}
			}
		}
	}

	return c_list[stored_index];
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
	first_diff = first_state.unemployed_2015 - first_state.unemployed_2007;
	second_diff = second_state.unemployed_2015 - second_state.unemployed_2007;
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
    struct county second_county)
{
	float first_diff, second_diff;
	first_diff = first_county.unemployed_2015 - first_county.unemployed_2007;
	second_diff = second_county.unemployed_2015 - second_county.unemployed_2007;
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
**						int indentation_level:
**							How indented the data should be (single indent
**							is two spaces in this context).
**  Pre-Conditions:     The state is initialized fully.
*/
void display_state_data(
    struct state state_to_display,
    int indentation_level)
{
	std::string indent = "";

	for (int i = 0; i < indentation_level; i++)
	{
		indent += "  ";
	}

	HelperLib::print(
		indent + "Data of", state_to_display.name + ":"
	);
	HelperLib::print(
		indent + "  Median Income:\n   ",
		indent + std::to_string(state_to_display.med_income)
	);
	HelperLib::print(
		indent + "  Unemployment in 2007:\n   ",
		indent + std::to_string(state_to_display.unemployed_2007)
	);
	HelperLib::print(
		indent + "  Unemployment in 2015:\n   ",
		indent + std::to_string(state_to_display.unemployed_2015)
	);
	HelperLib::print(
		indent + "  Number of Counties:\n   ",
		indent + std::to_string(state_to_display.num_counties)
	);
	std::cout << "#=~"
			  << std::endl;
}


/*
**  Function:			display_county_data
**  Description:		Prints all the stored data about a county to cout.
**  Parameters:			stuct county county_to_display:
**							The struct county to display.
**						int indentation_level:
**							How indented the data should be (single indent
**							is two spaces in this context).
**  Pre-Conditions:     The county is initialized fully.
*/


void display_county_data(
    struct county county_to_display,
    int indentation_level)
{
	std::string indent = "";

	for (int i = 0; i < indentation_level; i++)
	{
		indent += "  ";
	}

	HelperLib::print(
		indent + "Data of", county_to_display.name, "County:"
	);
	HelperLib::print(
		indent + "  Median Income:\n   ",
		indent + std::to_string(county_to_display.med_income)
	);
	HelperLib::print(
		indent + "  Unemployment in 2007:\n   ",
		indent + std::to_string(county_to_display.unemployed_2007)
	);
	HelperLib::print(
		indent + "  Unemployment in 2015:\n   ",
		indent + std::to_string(county_to_display.unemployed_2015)
	);
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
		if (
			HelperLib::contains(
				HelperLib::toUpper(state_list[index].name),
				HelperLib::toUpper(search_key)
			)
		)
		{
			return state_list[index];
		}
	}

	struct state no_result = { .name = "no_result" };

	return no_result;
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
		if (
			HelperLib::contains(
				HelperLib::toUpper(state_to_expand.county_list[index].name),
				HelperLib::toUpper(search_key)
			)
		)
		{
			return state_to_expand.county_list[index];
		}
	}

	struct county no_result = { .name = "no_result" };

	return no_result;
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
    int num_states,
    int indentation_level)
{
	std::string indent = "";

	for (int i = 0; i < indentation_level; i++)
	{
		indent += "  ";
	}

	std::cout << indent
			  << "States Loaded:"
			  << std::endl;

	for (int index = 0; index < num_states; index++)
	{
		std::cout << indent
				  << "  "
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
    struct state state_to_expand,
    int indentation_level)
{
	std::string indent = "";

	for (int i = 0; i < indentation_level; i++)
	{
		indent += "  ";
	}

	std::cout << indent
			  << "Counties of "
			  << state_to_expand.name
			  << ":"
			  << std::endl;

	for (int index = 0; index < state_to_expand.num_counties; index++)
	{
		std::cout << indent
				  << "  "
				  << state_to_expand.county_list[index].name
				  << std::endl;
	}

	std::cout << "#=~"
			  << std::endl;
}
