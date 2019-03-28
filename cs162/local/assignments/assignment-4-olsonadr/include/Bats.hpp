/*
 *  Program:		Bats.hpp - Bats Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Bats class. Lists all include
 *                      statements and function prototypes for Bats class,
 *                      which represent "Super Bats" that carry the Player
 *                      to a random room when encountered.
 */

#ifndef BATS_HPP
#define BATS_HPP

#include <string>
#include <random>
#include "Event.hpp"

class Bats : public Event
{
    private:
        // Dimensions of the cave
        int cave_width;
        int cave_height;

    public:
        // Constructor
        Bats(int w, int h);

        // General
        std::string get_name()	     { return "Super Bats"; }
        std::string get_percept()    { return "You hear wings flapping."; }
        std::string get_enter_text();
        bool handle_player(Player * p);
};

#endif
