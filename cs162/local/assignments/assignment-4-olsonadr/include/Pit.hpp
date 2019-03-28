/*
 *  Program:		Pit.hpp - Pit Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Pit class. Lists all include
 *                      statements and function prototypes for Pit class.
 *                      Which represent "Bottomless Pits" that kill the
 *                      Player when walked over.
 */

#ifndef PIT_HPP
#define PIT_HPP

#include <string>
#include "Event.hpp"

class Pit : public Event
{
    public:
        // General
        std::string get_name()	    { return "Bottomless Pit"; }
        std::string get_percept()   { return "You feel a breeze."; }
        std::string get_enter_text();
        bool handle_player(Player * p);
};

#endif
