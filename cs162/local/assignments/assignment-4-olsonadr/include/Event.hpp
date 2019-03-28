/*
 *  Program:		Event.hpp - Event Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Event class. Lists all include
 *                      statements and function prototypes for Event class.
 */

#ifndef EVENT_HPP
#define EVENT_HPP

#ifndef GAME_IS_OVER
#define GAME_IS_OVER true
#endif
#ifndef GAME_NOT_OVER
#define GAME_NOT_OVER false
#endif

#include <string>
#include "Player.hpp"

class Event
{
    public:
        // Accessors
        virtual std::string get_name() = 0;

        // General
        virtual bool handle_player(Player * p) = 0;
        virtual std::string get_percept() = 0;
        virtual std::string get_enter_text() = 0;
};

#endif
