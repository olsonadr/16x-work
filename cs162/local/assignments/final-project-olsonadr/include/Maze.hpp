/*
 * Maze Class Header File
 */

#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <fstream>
#include "MazeLevel.hpp"

class Maze
{
    private:
        int maze_width, maze_height;
        MazeLevel ** levels;
        int n_levels;
        int n_moves_made;
        int curr_level;
        int rounds_appeased;
        bool corners_count;

    public:
        // Constructors, etc.
        Maze(std::string maze_file);
        ~Maze();

        // Functions
        void level_setup();
        std::vector<char> level_moves();
        void go_up_level();
        void reset_to_start() { this->curr_level = 0; }

        int get_rounds_appeased()		{ return this->rounds_appeased; }
        void set_rounds_appeased(int new_val)	{ this->rounds_appeased = new_val; }
        void decrement_rounds_appeased()	{ this->rounds_appeased--; }
        void increment_rounds_appeased_by(int val) { this->rounds_appeased += val;}
        int get_n_moves_made()			{ return this->n_moves_made; }
        int get_n_levels()			{ return this->n_levels; }
        void set_corners(bool val)		{ this->corners_count = val; }
        int get_curr_level()			{ return this->curr_level; }

        // From MazeLevel
        void add_to(int i, MazePerson * new_person);
        void add_to_all(MazePerson * new_person);
        void display_level();
        void display_level_ta();
        void reset_curr_level();
        bool check_intersection(std::string type_a, std::string type_b, int r, bool c);
        bool check_intersection(int x, int y, std::string type, int r, bool c);
        MazeLocation * get_location(int m_row, int m_col);
};

#endif
