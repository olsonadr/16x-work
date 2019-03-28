/*
 * Instructor Class Implementation
 */

#include "Instructor.hpp"

char Instructor::get_move()
{
    return ' ';
}


/*
 * Pre-condition:   new_x and new_y are in bounds
 */
void Instructor::move_to(int new_x, int new_y)
{
    this->x_pos = new_x;
    this->y_pos = new_y;
    this->has_moved = true;
}
