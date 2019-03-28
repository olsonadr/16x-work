/*
 * Program:		hunt_the_wumpus.cpp - Hunt the Wumpus Interface File
 * Author:		Nick Olson
 * Date:		02/26/2019
 * Description:		Takes the dimensions of the cave as command-line parameter, only
 *			    proceeding if there is an argument provided and it is an int
 *			    greater than or equal to 4 and less than or equal to 20.
 *			    main() returns 0 on successful runtime, 1 for no argument
 *			    given, 2 for non-integer argument, 3 for dimension less than
 *			    4 or greater than 12.
 */

#include <iostream>
#include "Game.hpp"

#include <termios.h>
#include "Window.hpp"
#include "Console.hpp"

int main(int argc, char * argv[])
{
    int cave_dimension = 0;

    if (argc < 2)
    {
        std::cerr << "Must provide dimension of the cave, quitting..."
                  << std::endl;

        return 1;
    }
    else
    {
        const char * input = argv[1];
        int n_digits = 0;

        while (input[n_digits] != '\0')
        {
            if (input[n_digits] < '0' ||
                    input[n_digits] > '9')
            {
                std::cerr << "Dimension must be an integer, quitting..."
                          << std::endl;

                return 2;
            }
            else
            {
                cave_dimension *= 10;
                cave_dimension += int(input[n_digits] - '0');
                n_digits++;
            }
        }
    }

    if (cave_dimension < 4 ||
            cave_dimension > 12)
    {
        std::cerr << "Dimension must be in range [4,12], quitting..."
                  << std::endl;

        return 3;
    }

    Game g(cave_dimension, cave_dimension);
    g.setup();

    /* Game Loop */
    while (true)
    {
        bool game_over = false;

        //g.print_map();
        game_over = g.handle_input();

        if (game_over)
        {
            bool new_round = g.game_over_screen();

            if (new_round == false)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }

    g.cleanup();
    return 0;
}
