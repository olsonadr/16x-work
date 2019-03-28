/*
 * Maze Location Abstract Class Header File
 */

#ifndef MAZE_LOCATION_HPP
#define MAZE_LOCATION_HPP

class MazeLocation
{
    public:
        virtual bool is_occupiable() = 0;
        virtual char get_display_character() = 0;
};

#endif
