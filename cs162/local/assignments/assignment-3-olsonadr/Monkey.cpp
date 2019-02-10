/*
 *  Program:		Monkey.cpp - Monkey Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/04/19
 *  Description:	The implementation of the Monkey class described in
 *                      Monkey.hpp, objects of which represent... 
 */

#include "Monkey.hpp"

/*                                                                                      -
 *  Function:   		Monkey::get_revenue()
 *  Description:		a
 *  Returns:            _ as a int
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    a
 */
int Monkey::get_revenue(bool is_boom)
{
    int total = Animal::get_revenue();
    if (is_boom)
    {
        std::mt19937 rng(time(NULL));
        std::uniform_int_distribution<int> gen(250, 500);
        total += gen(rng);
    }
    return total;
}