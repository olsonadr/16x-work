/*
 * Nicholas Olson - CS 162 - March 20, 2019
 * Primary application file for the Escape CS 162 Game.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>

#include "Maze.hpp"
#include "IntrepidStudent.hpp"
#include "TA.hpp"
#include "Instructor.hpp"
#include "Console.hpp"

void read_maze_dir(std::vector<std::string> & files, std::string dir)
{
    DIR * dir_ptr = opendir(dir.c_str());
    struct dirent * dirent_ptr;

    while (ENOENT != errno && ((dirent_ptr = readdir(dir_ptr)) != NULL))
    {
        if (dirent_ptr->d_name[0] != '.')
        {
            files.push_back(dirent_ptr->d_name);
        }
    }

    closedir(dir_ptr);
}

void clear_maze_vec(std::vector<std::string> & files)
{
    files.clear();
}

int main()
{
    srand(time(NULL));
    Console my_c(0, 0, 0, 0, 1, STATIC_ELEMENT, "my_c");

    // Menu
    bool menu_keep_going = true;
    bool play_game = false;

    /* settings */
    bool show_hitboxes = false;
    bool hard_hitboxes = false;

    /* read map directory */
    std::vector<std::string> files;
    std::string dir_a = "../maps";
    std::string dir_b = "maps";
    read_maze_dir(files, dir_a);

    if (files.size() < 1)
    {
        read_maze_dir(files, dir_b);
    }

    /* file name to be played */
    std::string map_name;

    /* menu loop */
    while (menu_keep_going)
    {
        system("tput clear");

        std::cout << "Escape from CS 162!" << std::endl << std::endl;

        std::cout << "(0) New Game" << std::endl
                  << "(1) Settings" << std::endl
                  << "(2) Help" << std::endl
                  << "(q) Quit" << std::endl << std::endl;

        char input = toupper(my_c.unbuffed_char_input());

        if (input == '0')
        {
            bool new_game_keep_going = true;
            int page_n = 0;

            while (new_game_keep_going)
            {
                system("tput clear");

                std::cout << "New Game" << std::endl << std::endl;
                std::cout << "Choose Maze File (in maps directory):" << std::endl;

                int list_max = 10;
                int max_pages = int((files.size() - 1) / list_max) + 1;
                std::vector<std::string>::iterator file_iter = files.begin();

                for (int i = 0; i < list_max; i++)
                {
                    int file_i = i + page_n * list_max;

                    if (file_iter + file_i >= files.end())
                    {
                        /* out of bounds of files */
                        break;
                    }

                    std::cout << "(" << i << ") " << *(file_iter + file_i) << std::endl;
                }

                std::cout << std::endl << "Page (" << (page_n + 1) << "/" << max_pages << ")" << std::endl
                          << std::endl;

                std::cout << "(,) Previous Page" << std::endl
                          << "(.) Next Page" << std::endl
                          << "(r) Refresh List" << std::endl
                          << "(q) Back to Menu" << std::endl << std::endl;

                char m_input = toupper(my_c.unbuffed_char_input());

                if (m_input >= '0' && m_input <= '0' + list_max)
                {
                    int choice = (m_input - '0') + (page_n * list_max);

                    if (file_iter + choice < files.end())
                    {
                        /* in bounds */
                        new_game_keep_going = false;
                        menu_keep_going = false;
                        play_game = true;
                        map_name = files.at(choice);
                    }
                }
                else if (m_input == ',')
                {
                    if (page_n > 0)
                    {
                        page_n--;
                    }
                }
                else if (m_input == '.')
                {
                    if (page_n < max_pages - 1)
                    {
                        page_n++;
                    }
                }
                else if (m_input == 'R')
                {
                    clear_maze_vec(files);
                    read_maze_dir(files, dir_a);

                    if (files.size() < 1)
                    {
                        read_maze_dir(files, dir_b);
                    }
                }
                else if (m_input == 'Q')
                {
                    new_game_keep_going = false;
                }
            }
        }
        else if (input == '1')
        {
            bool settings_keep_going = true;

            while (settings_keep_going)
            {
                system("tput clear");

                std::cout << "Settings Title" << std::endl << std::endl;

                std::cout << "(0) Show Hitboxes (TA danger zone)" << std::endl
                          << "    [currently " << ((show_hitboxes) ? ("visible") : ("hidden")) << "]" << std::endl
                          << "(1) Hitbox Style (plus or square shape)" << std::endl
                          << "    [currently " << ((hard_hitboxes) ? ("square") : ("plus")) << "]" << std::endl
                          << "(q) Back to Menu" << std::endl << std::endl;

                char s_input = toupper(my_c.unbuffed_char_input());

                if (s_input == 'Q')
                {
                    settings_keep_going = false;
                }
                else if (s_input == '0')
                {
                    show_hitboxes = !show_hitboxes;
                }
                else if (s_input == '1')
                {
                    hard_hitboxes = !hard_hitboxes;
                }
            }
        }
        else if (input == '2')
        {
            bool help_keep_going = true;

            while (help_keep_going)
            {
                system("tput clear");

                std::cout << "Help Title" << std::endl << std::endl;

                std::cout << "Help information..." << std::endl << std::endl;

                std::cout << "(q) Back to menu" << std::endl << std::endl;

                char h_input = toupper(my_c.unbuffed_char_input());

                if (h_input == 'Q')
                {
                    help_keep_going = false;
                }
            }
        }
        else if (input == 'Q')
        {
            menu_keep_going = false;
        }
        else
        {
            // Invalid input
        }

    }

    // Clear
    system("tput clear");

    // Open map and play game
    if (play_game == true)
    {
        try
        {
            std::string maze_dir = "maps/";
            Maze game_maze(maze_dir + map_name);

            // Set attributes
            game_maze.set_corners((hard_hitboxes) ? (true) : (false));

            // Add people
            IntrepidStudent student;
            student.give_console(&my_c);
            Instructor hess;
            TA ta_a;
            TA ta_b;
            TA ta_c;
            game_maze.add_to_all(&student);
            game_maze.add_to_all(&ta_a);
            game_maze.add_to_all(&ta_b);
            game_maze.add_to_all(&ta_c);
            game_maze.add_to(2, &hess);

            // Setup first level
            game_maze.level_setup();

            // Display Maze
            game_maze.display_level();

            // Game Loop
            bool keep_going = true;

            while (keep_going)
            {
                // Consistent changes
                if (game_maze.get_rounds_appeased() > 0)
                {
                    game_maze.set_rounds_appeased(game_maze.get_rounds_appeased() - 1);
                }


                // Get moves
                std::vector<char> special = game_maze.level_moves();


                // Handle special moves
                bool check_logic = true;
                std::vector<char>::iterator ptr;

                for (ptr = special.begin(); ptr < special.end(); ptr++)
                {
                    switch (*ptr)
                    {
                        default:
                            break;

                        case '~':
                            check_logic = false; // Unrecognized input, don't penalize
                            break;

                        case 'Q':
                            keep_going = false; // Quit
                            check_logic = false;
                            break;

                        case 'R':
                            game_maze.reset_curr_level();
                            game_maze.set_rounds_appeased(0);
                            student.take_skills();
                            check_logic = false;
                            break;

                        case 'P':
                            if (student.get_n_skills() > 0)
                            {
                                student.use_skill();
                                game_maze.set_rounds_appeased(game_maze.get_rounds_appeased() + 10);
                            }

                            break;

                        case 'U':
                            OpenSpace * p_loc = static_cast<OpenSpace *>(
                                                    game_maze.get_location(student.get_y_pos(), student.get_x_pos()));

                            if (p_loc->get_has_end())
                            {
                                game_maze.go_up_level();
                                game_maze.reset_curr_level();
                                check_logic = false;
                            }

                            break;
                    }
                }

                if (check_logic == true) // not a wasted turn
                {
                    // Check for intersection problems
                    bool ta_intersect = false;
                    bool instructor_intersect = false;

                    OpenSpace * p_loc = static_cast<OpenSpace *>(
                                            game_maze.get_location(student.get_y_pos(), student.get_x_pos()));

                    if (p_loc->get_has_p_skill() == true)
                    {
                        student.add_skill();
                        p_loc->set_has_p_skill(false);
                    }

                    if (game_maze.check_intersection("IntrepidStudent", "TA", 1, false) == true)
                    {
                        ta_intersect = true;
                    }

                    if (game_maze.check_intersection("IntrepidStudent", "Instructor", 1, true) == true)
                    {
                        instructor_intersect = true;
                    }


                    // Handle these problems
                    if (instructor_intersect == true)
                    {
                        if (student.get_n_skills() >= 3)
                        {
                            std::cout << "You win! Press enter..." << std::endl;
                            getchar();
                            keep_going = false;
                        }
                        else
                        {
                            std::cout << "You don't have enough skill so you FAIL! Press enter..." << std::endl;
                            getchar();
                            game_maze.reset_to_start();
                            game_maze.reset_curr_level();
                            game_maze.set_rounds_appeased(0);
                            student.take_skills();
                        }
                    }
                    else if (ta_intersect == true)
                    {
                        if (game_maze.get_rounds_appeased() <= 0)
                        {
                            std::cout << "You were terrified by a TA and lose all your skills! Press enter..." <<
                                      std::endl;
                            getchar();
                            game_maze.reset_curr_level();
                            student.take_skills();
                        }
                    }

                }

                // Clear
                system("tput clear");

                // Display Maze
                if (show_hitboxes == true)
                {
                    game_maze.display_level_ta();
                }
                else
                {
                    game_maze.display_level();
                }

                std::cout << "Skills    =  " << student.get_n_skills() << std::endl;
                std::cout << "Appeased  =  " << game_maze.get_rounds_appeased() << std::endl;
            }
        }
        catch (const char *& e)
        {
            std::cerr << e << std::endl;
        }
        catch (std::string & e)
        {
            std::cerr << e << std::endl;
        }
    }

    return 0;
}
