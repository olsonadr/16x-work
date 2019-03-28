/*
 * Open Space Implementation
 */

#include "OpenSpace.hpp"

char OpenSpace::get_display_character()
{
    if (this->has_player)
    {
        return 'S';
    }
    else if (this->has_end)
    {
        return '^';
    }
    else if (this->has_ta)
    {
        return 'T';
    }
    else if (this->has_instructor)
    {
        return '%';
    }
    else if (this->has_p_skill)
    {
	return 'P';
    }
    else
    {
        return ' ';
    }
}


void OpenSpace::reset_contents()
{
    this->has_start = false;
    this->has_end = false;
    this->has_player = false;
    this->has_ta = false;
    this->has_instructor = false;
    this->has_p_skill = false;
}


void OpenSpace::reset_moving_contents()
{
    this->has_player = false;
    this->has_ta = false;
}
