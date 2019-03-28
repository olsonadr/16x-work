/*
 *  Program:		Room.hpp - Room Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Room class, lists all include
 *                      statements and function prototypes for Room class,
 *                      which represent the Rooms in the Wumpus's cave.
 */

#ifndef ROOM_HPP
#define ROOM_HPP

#ifndef GAME_IS_OVER
#define GAME_IS_OVER true
#endif
#ifndef GAME_NOT_OVER
#define GAME_NOT_OVER false
#endif

#include <string>

#include "Event.hpp"
#include "Player.hpp"

class Room
{
    private:
        Event * contained_event;
        bool has_event;

    public:
        // Constructor
        Room() : has_event(false), contained_event(nullptr) {}

        // Accessors
        bool get_has_event() { return this->has_event; }

        // Mutators
        void set_event(Event * new_event);
        void clear_event();

        // Event Pass-Throughs
        std::string get_percept();
        std::string get_event_name();
	std::string get_enter_text();
        bool handle_player(Player * p);

        // Misc
        bool has_wumpus();
};

#endif
