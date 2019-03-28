/*
 *  Program:		Gold.hpp - Gold Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Gold class. Lists all include
 *                      statements and function prototypes for Gold class,
 *                      objects of which are Events that represent the hoard
 *                      of the Wumpus' Gold and one of the primary objectives
 *                      of the hunt-the-wumpus Game.

 */

#ifndef GOLD_HPP
#define GOLD_HPP

#include <string>
#include "Event.hpp"

class Gold : public Event
{
    public:
        // General
        std::string get_name()	    { return "Gold"; }
        std::string get_percept()   { return "You see a glimmer nearby."; }
        std::string get_enter_text();
        bool handle_player(Player * p);
};

#endif
