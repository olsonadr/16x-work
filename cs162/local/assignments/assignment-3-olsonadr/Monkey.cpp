/*
 *  Program:		Monkey.cpp - Monkey Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/04/19
 *  Description:	The implementation of the Monkey class described in
 *                      Monkey.hpp, objects of which represent...
 */

#include "Monkey.hpp"

/*                                                                                      -
 *  Function:		Monkey::boom_rev()
 *  Description:	Determines and returns how much this Monkey makes on top of its
 *			    usual revenue, only called when the special event 'boom in
 *			    attendance' occurs.
 *  Returns:            The amount it earns extra (250 - 500) as an int.
 *  Pre-conditions:     All fields have been instantiated, attendance boom has occured.
 *  Post-conditions:    Nothing has changed, bonus returned.
 */
int Monkey::boom_rev()
{
    std::mt19937 rng(time(NULL));
    std::uniform_int_distribution<int> gen(250, 500);
    return gen(rng);
}
