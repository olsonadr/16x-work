/*
 * IntrepidStudent Class Implementation
 */

#include "IntrepidStudent.hpp"

char IntrepidStudent::get_move()
{
    int n_legal_moves = 8;
    char legal_moves[] =
    {
        'W', 'A', 'S', 'D',
        'U', 'P', 'Q', 'R'
    };

    // Get input using best available method
    char input;

    if (this->has_console == false)
    {
        std::cin >> input;
    }
    else
    {
        input = this->my_console->unbuffed_char_input();
    }

    input = toupper(input);

    for (int i = 0; i < n_legal_moves; i++)
    {
        if (input == legal_moves[i])
        {
            return toupper(input);
        }
    }

    return '~'; // wasted move
}


/*
 * Pre-condition:   new_x and new_y are in bounds
 */
void IntrepidStudent::move_to(int new_x, int new_y)
{
    this->x_pos = new_x;
    this->y_pos = new_y;
    this->has_moved = true;
}


/*
 * Post-condition:  the IntrepidStudent now has a Console it uses for unbuffered
 *		    input, rather than using cin as by default.
 */
void IntrepidStudent::give_console(Console * my_console)
{
    this->my_console = my_console;
    this->has_console = true;
}
