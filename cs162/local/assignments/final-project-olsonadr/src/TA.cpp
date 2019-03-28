/*
 * TA Class Implementation
 */

#include "TA.hpp"

char TA::get_move()
{
    int rand_int = rand() % 4;

    switch (rand_int)
    {
        default:
            return 'W';
            break;

        case 1:
            return 'A';
            break;

        case 2:
            return 'S';
            break;

        case 3:
            return 'D';
            break;
    }
}


/*
 * Pre-condition:   new_x and new_y are in bounds
 */
void TA::move_to(int new_x, int new_y)
{
    this->x_pos = new_x;
    this->y_pos = new_y;
    this->has_moved = true;
}
