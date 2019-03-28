/*
 * Wall Class Header File
 */

#ifndef WALL
#define WALL

#include "MazeLocation.hpp"

class Wall : public MazeLocation
{
    public:
        bool is_occupiable()		{ return false; }
        char get_display_character()	{ return '#'; }
};

#endif
