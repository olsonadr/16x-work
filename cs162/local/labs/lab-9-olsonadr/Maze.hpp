/*
 * Maze Class Header File
 */

#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <iostream>
#include "MazeLocation.hpp"
#include "OpenSpace.hpp"
#include "Wall.hpp"
#include "Explorer.hpp"

class Maze
{
    private:
        std::vector<std::vector<MazeLocation *> > locations;
        int maze_width, maze_height;

    public:
        Maze(const char ** m_str, int m_width, int m_height);
        ~Maze();

        MazeLocation * get_location(int m_row, int m_col);
        void display_maze();
        void display_maze_occupiable();

	void set_init_pos(Explorer * e);
};

#endif
