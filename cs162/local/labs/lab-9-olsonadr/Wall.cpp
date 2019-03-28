/*
 * Wall Class Implementation
 */

#include "Wall.hpp"

bool Wall::is_occupiable()
{
    return false;
}


char Wall::get_display_character()
{
    return '#';
}
