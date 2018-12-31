/*
**  Program:	   ass3.cpp - Assignment #3: Various Functions
**  Author:		   Nick Olson
**  Date:		   12/26/2018
**  Description:   Runs and prints the results of various functions.
*/

#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;


/*
**  Function:			~check_range
**  Description:		~Indicates if the provided number is in the specified range.
**  Parameters:			~lower_bound - lower bound of the range to check.
**						~upper_bound - upper bound of the range to check.
**						~test_value  - the value the functions checks against the passed range of values.
**  Pre-Conditions:     ~lower_bound is smaller than upper_bound.
*/
bool check_range(int lower_bound, int upper_bound, int test_value)
{
	if (test_value >= lower_bound && test_value <= upper_bound)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*
 *  Function:			a
 *  Description:		Indicates if a given string is an integer
 *  Parameters:
 *  Pre-Conditions:
 *  Post-Conditions:
 */
bool is_int(const char *num)
{
	float f_result = strtol(num, NULL, 0);
	int i_result = (int) f_result;
	
	cout << "i_result" << i_result << endl;
	cout << "f_result" << f_result << endl;

	if ((i_result != 0 || strcmp(num, "0") == 0) && i_result == f_result)
	{
		//cout << "\"" << num << "\" --> " << i_result << endl;
		return true;
	}
	else
	{
		//cout << "\"" << num << "\" can't be converted to type int!" << endl;
		return false;
	}
}

int main()
{
	cout << "Testing that shit:" << endl;
	int lower_bound;
	int upper_bound;
	int test_value;
	cout << "check_range:" << endl << "lower_bound = ";
	cin >> lower_bound;
	cout << "upper_bound = ";
	cin >> upper_bound;
	cout << "test_value = ";
	cin >> test_value;
	cout << "result: " << check_range(lower_bound, upper_bound,
			test_value) << endl;
	string num;
	cout << endl << "is_int:" << endl << "num = ";
	cin >> num;
	cout << "result: " << is_int(num.c_str()) << endl;
	return 0;
}
