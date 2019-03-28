/*
 * Game Class Header File
 */

#ifndef GAME_HPP
#define GAME_HPP

// Includes
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>

// Game Stuff
#include "MazePerson.hpp"
#include "IntrepidStudent.hpp"
#include "TA.hpp"
#include "Instructor.hpp"
#include "MazeLocation.hpp"
#include "Wall.hpp"
#include "OpenSpace.hpp"
#include "MazeLevel.hpp"
#include "Maze.hpp"

// UI Stuff
#include "Window.hpp"
#include "Panel.hpp"
#include "Console.hpp"
#include "Label.hpp"
#include "Alert.hpp"
#include "Border.hpp"

class Game
{
    private:
        // Game Stuff
        Maze * game_maze;
        bool show_hitboxes, hard_hitboxes;
        bool maze_loaded;
        std::string chosen_map;
        IntrepidStudent student;
        Instructor hess;
        TA ta_a, ta_b, ta_c;
        bool maze_allocated;

        // Game UI Stuff
        Window game_w;

        // Menu UI Stuff
        Window * menu_w;
        Console game_c;
        std::string * load_pages;
        std::string * info_pages;
        int n_load_pages;
        int n_info_pages;
        bool maps_loaded;
        std::string map_dir;
        std::vector<std::string> map_files;
        int load_list_max;

        // Game Functions
	void display_maze();

        // Menu Functions
        void read_maze_dir(std::vector<std::string> & files, std::string dir);
        void fill_load_pages();
        void clear_maze_vec(std::vector<std::string> & files);
        void options_menu();
        void load_menu(bool & menu_keep_going);
        void info_menu();

    public:
        // Constructors, etc.
        Game(std::string map_dir);
        ~Game();

        // Accessor
        bool get_maze_loaded() { return this->maze_loaded; }

        // Menu Functions
        void setup_menu();
        void display_menu();

        // Game Functions
        void setup_game();
        bool game_turn();
};

#endif
