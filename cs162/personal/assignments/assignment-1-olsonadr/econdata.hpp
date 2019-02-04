/*
**  Program:		econdata.hpp - Economic data viewer header file.
**  Author:		Nick Olson
**  Date:		01/07/2019
**  Description:	Header file for the econdata program. This defines the structures of
**			the program as well as the prototypes for each function used.
*/


// iostream for terminal-based user i/o
#include <iostream>
// fstream for file reading and parsing
#include <fstream>
// string for getline() functionality in file-reading
#include <string>
// help.h for my HelperLib library of helpful methods
#include "help.hpp"
// algorithm for sort method
#include <algorithm>


// Allocates an array of a specified number of states.
struct state * allocate_states(int);
// Reads data for a specified number of states from an input file stream into a given (pre-allocated) array.
void read_state_data(struct state *, int, std::ifstream &);
// Allocates an array of a specified number of counties.
struct county * allocate_counties(int);
// Reads data for a specified number of counties from an input file stream into a given (pre-allocated) array.
void read_county_data(struct county *, int, std::ifstream &);
// Releases all data (including county data) allocated to given state array.
void free_state_data(struct state *, int);
// Opens the file into the passed ifstream.
int open_file(int, char * [], std::ifstream &);
// Returns the number of states in the data file.
int get_num_states(std::ifstream &);
// Directs user through the menu system.
void menu_system(struct state *, int);
// Finds the state w/ the highest/lowest val of a given field.
struct state find_state(struct state *, int, std::string, std::string);
// Finds the county w/ the highest/lowest val of a given field.
struct county find_county(struct state, std::string, std::string);
// Compares two states by their changes in unemployment.
bool compare_state_employment(struct state, struct state);
// Compares two states by their median income.
bool compare_state_income(struct state, struct state);
// Compares two counties by their changes in unemployment.
bool compare_county_employment(struct county, struct county);
// Compares two states by their median income.
bool compare_county_income(struct county, struct county);
// Displays all the data about a specific state struct.
void display_state_data(struct state, int indentation_level = 0);
// Displays all the data about a specific county struct.
void display_county_data(struct county, int indentation_level = 0);
// Finds and returns the first state containing given substring.
struct state search_for_state(struct state *, int, std::string);
// Finds and returns the first county containing given substring.
struct county search_for_county(struct state, std::string);
// Prints the names of all states to cout, one per line.
void display_states(struct state *, int, int indentation_level = 0);
// Prints the names of all counties in a state to cout, one per line.
void display_counties(struct state, int indentation_level = 0);

// Holds all the relevent data that each county has.
struct county
{
	std::string name;
	float unemployed_2007;
	float unemployed_2015;
	int med_income;
};

// Holds all the relevent data that each state has.
struct state
{
	std::string name;
	float unemployed_2007;
	float unemployed_2015;
	int med_income;
	struct county * county_list;
	int num_counties;
};
