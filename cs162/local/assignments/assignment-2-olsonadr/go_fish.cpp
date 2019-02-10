/*
 *  Program:		go_fish.cpp - go fish game interface file
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	Holds the interface main method that holds the main
 *                      game loop go_fish and handles input for whether
 *                      the user wants to play again when the game ends.
 */

#include <iostream>
#include "help.hpp"
#include "Game.hpp"

int main()
{
    std::system("CLS");
    std::system("clear");

    std::cout << "Welcome to Go Fish!"
              << std::endl
              << std::endl
              << "You'll be challenging a state-of-the-art AI in this"
              << std::endl
              << "battle of wits! Press enter when you dare to begin..."
              << std::endl;

    std::getchar();

    // Game Loop
    bool keep_going = true;
    bool is_game_over = false;
    Game g;
    g.setup();
    while (keep_going)
    {
        int secret = g.player_turn();
        if (secret == 1)
        {
            is_game_over = g.check_game_over(true);
        }
        else
        {
            g.cpu_turn();
        }

        if (is_game_over || g.check_game_over())
        {
            int input = HelperLib::getIntInputInRange(
                "Would you like to play again? (0 or 1)",
                0, 1, 0);

            if (input == 1)
            {
                std::cout << "Here we go! Press enter when ready..."
                          << std::endl;

                std::getchar();
                g.reset();
            }
            else
            {
                keep_going = false;
                std::cout << "Well it's sad to see you go... Thanks for playing!"
                          << std::endl
                          << "#=~"
                          << std::endl;
            }
        }
    }

    return 0;
}