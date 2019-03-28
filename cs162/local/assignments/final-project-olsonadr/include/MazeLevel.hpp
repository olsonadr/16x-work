/*
 * MazeLevel Class Header File
 */

#ifndef MAZE_LEVEL_HPP
#define MAZE_LEVEL_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "MazeLocation.hpp"
#include "OpenSpace.hpp"
#include "Wall.hpp"
#include "IntrepidStudent.hpp"
#include "Instructor.hpp"

class MazeLevel
{
    private:
        std::vector<std::vector<MazeLocation *> > locations;
        std::vector<MazePerson *> people;
        int maze_width, maze_height;
        int starting_x, starting_y;
        int n_people;

        void handle_movement(int person_i, char move);
        void update_bools(int loc_x, int loc_y);

    public:
        MazeLevel(std::ifstream & maze_file, int m_width, int m_height);
        ~MazeLevel();

        void add_person(MazePerson * new_person);

        MazeLocation * get_location(int m_row, int m_col);
        std::vector<char> get_moves();
        void display_maze();
        void display_maze_occupiable();
        void display_maze_ta(bool corners);
        void display_maze_instructor();

        void reset_level();
        bool check_intersection(std::string type_a,
                                std::string type_b,
                                int r, bool corners);
        bool check_intersection(int x, int y,
                                std::string type,
                                int r, bool corners);
};

#endif
