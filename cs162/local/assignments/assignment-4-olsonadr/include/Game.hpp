/*
 *  Program:		Game.hpp - Game Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Game class, lists all include
 *                      statements and function prototypes for Game class,
 *                      which handles and presents all aspects of the Game.
 */

#ifndef GAME_HPP
#define GAME_HPP

#ifndef GAME_IS_OVER
#define GAME_IS_OVER true
#endif
#ifndef GAME_NOT_OVER
#define GAME_NOT_OVER false
#endif

#define MAX_INPUT_LENGTH 100

// Standard Stuff
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <random>
#include <vector>

// Game Classes
#include "Player.hpp"
#include "Room.hpp"
#include "Event.hpp"
#include "Bats.hpp"
#include "Gold.hpp"
#include "Pit.hpp"
#include "Wumpus.hpp"

// UI cpp_panels Library Stuff
#include "Window.hpp"
#include "Panel.hpp"
#include "Label.hpp"
#include "Console.hpp"
#include "Border.hpp"
#include "List.hpp"


class Game
{
    private:
	// Game Fields
        Player * p;
        std::vector<std::vector<Room *>> rooms;
        int cave_width, cave_height;
	Room * init_wump_room;
	Room * init_gold_room;
        int exit_x, exit_y;

	// UI Fields
	Window * game_window;
	Label * player_label;
	Console * game_console;
	Label * num_arrows_label;
	Label * wumpus_check_label;
	Label * gold_check_label;
	Alert * general_alert;

	int room_w, room_h;
	int p_l_x_off, p_l_y_off;
	int cave_str_x, cave_str_y;

	// Private Methods
	void generate_map_str(char *& rooms_str, char *& player_str);
	void update_p_str_pos();
	void update_ui();

    public:
        // Constructor + Destructor
        Game(int cave_w, int cave_h);
        ~Game();

        // General
        void setup();
        void cleanup();
        void generate_percepts();
        bool handle_input();
        bool shoot_arrow(std::string direction);
        bool enter_room(); /*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*/
        bool game_over_screen(); /*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*/
        Room * find_wumpus_room();

        // Setup Functions
        void generate_map(int width, int height);
        Room * add_to_rand_empty_room(Event * to_add);
        void move_p_to_rand_empty_room();

        // Debug Functions
        void print_map();

        // I/O Functions
        std::string input(std::string prompt = "");
        std::string get_char_input(std::string prompt = "");
        void output(std::string message = "");
        void alert_and_pause(std::string message = "");
};

#endif
