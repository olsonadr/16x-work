/*
 * Open Space Implementation
 */

#include "OpenSpace.hpp"

bool OpenSpace::is_occupiable()
{
    return true;
}


char OpenSpace::get_display_character()
{
    if (this->has_player)
    {
        return 'X';
    }
    else if (this->has_start)
    {
        return '@';
    }
    else if (this->has_end)
    {
        return '^';
    }
    else
    {
        return ' ';
    }
}


bool OpenSpace::get_has_start()
{
    return this->has_start;
}


bool OpenSpace::get_has_end()
{
    return this->has_end;
}


bool OpenSpace::get_has_player()
{
    return this->has_player;
}


void OpenSpace::set_has_start(bool new_val)
{
    this->has_start = new_val;
}


void OpenSpace::set_has_end(bool new_val)
{
    this->has_end = new_val;
}


void OpenSpace::set_has_player(bool new_val)
{
    this->has_player = new_val;
}


void OpenSpace::reset_contents()
{
    this->has_start = false;
    this->has_end = false;
    this->has_player = false;
}
