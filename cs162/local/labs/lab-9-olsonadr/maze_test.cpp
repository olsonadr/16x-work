/*
 * Maze class testing application
 */

#include <iostream>
#include <random>
#include <unistd.h>
#include "Maze.hpp"
#include "Explorer.hpp"
#include "maze_data.hpp"

int main()
{
    srand(time(NULL));

    Maze my_maze(MAZE_DATA, MAZE_WIDTH, MAZE_HEIGHT);
    Explorer my_explorer;

    my_maze.display_maze();

    std::cout << std::endl << "Press enter when ready for EXPLORATION!" << std::endl;
    getchar();

    // Game Loop
    bool keep_going = true;

    my_maze.set_init_pos(&my_explorer);

    while (keep_going)
    {
        /* Handle Movement */
        MazeLocation * current = my_maze.get_location(my_explorer.get_y_pos(),
                                 my_explorer.get_x_pos());
        int target_x = my_explorer.get_x_pos();
        int target_y = my_explorer.get_y_pos();

        char move = my_explorer.get_move();

        if (move == 'W')
        {
            target_y -= 1;
        }
        else if (move == 'A')
        {
            target_x -= 1;
        }
        else if (move == 'S')
        {
            target_y += 1;
        }
        else
        {
            target_x += 1;
        }

        MazeLocation * target = my_maze.get_location(target_y, target_x);

        /*printf("Curr x, y = %d, %d;\nTarget x, y = %d, %d;\n", my_explorer.get_x_pos(),
               my_explorer.get_y_pos(), target_x, target_y);*/

        if (target != nullptr && target->is_occupiable() == true)
        {
            OpenSpace * curr_loc = static_cast<OpenSpace *>(current);
            OpenSpace * target_loc = static_cast<OpenSpace *>(target);
            /* Is Valid Move */
            curr_loc->set_has_player(false);
            target_loc->set_has_player(true);
            my_explorer.move_to(target_x, target_y);
        }

        /* End Handle Movement */


        /* redisplay */
	system("clear");
        my_maze.display_maze();
        /* end redisplay */


        /* Check if at end */
        if (current->is_occupiable() == true)
        {
            OpenSpace * curr_loc = static_cast<OpenSpace *>(current);

            if (curr_loc->get_has_end() == true)
            {
                std::cout << "You've reached the end of the maze! Congrats!" << std::endl;
		keep_going = false;
            }
        }

        /* End check end */


        /* wait */
        sleep(.5);
        /* end wait */
    }

    return 0;
}
