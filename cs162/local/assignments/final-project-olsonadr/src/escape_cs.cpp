/*
 * Nicholas Olson - CS 162 - March 20, 2019
 * Description:	    Primary application file for the Escape CS 162 Game.
 *		    Requires nothing before launch; no command-line arguments.
 *		    Must be non-maximized terminal window before menu is displayed.
 */

#include <iostream>
#include "Game.hpp"
#include "Maze.hpp"
#include "IntrepidStudent.hpp"
#include "TA.hpp"
#include "Instructor.hpp"
#include "Console.hpp"

int main()
{
    srand(time(NULL));

    // Make sure I don't get failed because I
    //	didn't make it clear how to use the program
    std::cout << "Please un-maximize your terminal and hit enter when ready..."
	<< std::endl;
    getchar();

    // Actual program stuff
    Game * g = new Game("maps");
    g->setup_menu();
    g->display_menu();

    bool maze_loaded = g->get_maze_loaded();

    if (maze_loaded == true)
    {
        try
        {
            g->setup_game();

            // Game Loop
            bool keep_going = true;

            while (keep_going)
            {
                bool result = g->game_turn();

                if (result == false)
                {
                    keep_going = false;
                }
            }
        }
        catch (const char *& e)
        {
            delete g;
            std::cerr << e << std::endl;
            return 0;
        }
    }

    delete g;
    return 0;
}
