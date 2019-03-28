/*
 *  Program:		Wumpus.hpp - Wumpus Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Wumpus class. Lists all include
 *                      statements and function prototypes for Wumpus class,
 *                      which is an Event that kills the user when encountered.
 */

#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include <string>
#include "Event.hpp"

class Wumpus : public Event
{
    public:
        // General
        std::string get_name()	    { return "The Wumpus"; }
        std::string get_percept()   { return "You smell a terrible stench."; }
	std::string get_enter_text();
        bool handle_player(Player * p);
};

#endif
