/*
 * Wall Class Header File
 */

#ifndef WALL
#define WALL

#include "MazeLocation.hpp"

class Wall : public MazeLocation
{
    public:
        bool is_occupiable();
        char get_display_character();
};

#endif
