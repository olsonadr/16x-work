/*
 * Game Class Implementation
 */

#include "Game.hpp"

/*
 * Constructs the Game
 */
Game::Game(std::string map_dir)
    : show_hitboxes(false), hard_hitboxes(false),
      maze_loaded(false), map_dir(map_dir),
      maps_loaded(false), info_pages(new std::string[4]),
      game_c(0, 0, 1, 1, 1, DYNAMIC_ELEMENT, "game_c"),
      load_list_max(6), n_info_pages(4),
      game_w(30, 30), maze_allocated(false)
{
    fill_load_pages();
}


/*
 * Destructs the Game
 */
Game::~Game()
{
    this->game_w.close();
    this->menu_w->close();
    delete this->menu_w;
    delete[] this->info_pages;

    if (this->maps_loaded == true)
    {
        delete[] this->load_pages;
    }

    if (this->maze_allocated == true)
    {
        delete this->game_maze;
    }
}


/*
 * Fills the load_pages fields with the correct strings by reading the files
 *  from the directory pointed to in map_dir, trying both as if the executable
 *  is being run from the folder containing the passed dir and if the executable
 *  is being run from the bin folder (so we must go out once first).
 */
void Game::fill_load_pages()
{
    clear_maze_vec(this->map_files);

    read_maze_dir(this->map_files, this->map_dir);

    if (this->map_files.size() < 1)
    {
        read_maze_dir(this->map_files, "../" + this->map_dir);
    }

    int page_n = 0;
    this->n_load_pages = (this->map_files.size() - 1) / this->load_list_max + 1;

    if (this->maps_loaded == true)
    {
        delete[] this->load_pages;
    }

    this->load_pages = new std::string[this->n_load_pages];
    this->maps_loaded = true;

    for (int i = 0; i < this->map_files.size(); i++)
    {
        if (i >= (page_n + 1) * this->load_list_max)
        {
            *(this->load_pages[page_n].end() - 1) = '\0';
            page_n++;
        }

        this->load_pages[page_n] +=
            "(" + std::to_string(i % this->load_list_max) + ") " + this->map_files[i] + "\n";
    }
}


/*
 * Stores the filenames of every file in the passed maps directory in the
 *  passed std::string vector reference.
 */
void Game::read_maze_dir(std::vector<std::string> & files, std::string dir)
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


/*
 * Clears the passed std::string vector of elements.
 */
void Game::clear_maze_vec(std::vector<std::string> & files)
{
    files.clear();
}


/*
 * Sets up the Game objects for play
 */
void Game::setup_game()
{
    // Make Maze
    this->game_maze = new Maze(this->map_dir + "/" + chosen_map);
    this->maze_allocated = true;

    // Set attributes
    this->game_maze->set_corners((hard_hitboxes) ? (true) : (false));

    // Add people
    this->student.give_console(&this->game_c);
    this->game_maze->add_to_all(&this->student);
    this->game_maze->add_to_all(&this->ta_a);
    this->game_maze->add_to_all(&this->ta_b);
    this->game_maze->add_to_all(&this->ta_c);
    this->game_maze->add_to(this->game_maze->get_n_levels() - 1, &this->hess);

    // Setup first level
    this->game_maze->level_setup();

    // Setup game
    this->game_w.open();

    // Clear screen
    system("tput clear");

    // Display
    display_maze();
}


/*
 * A single game turn, false is returned if the game is over and quit.
 */
bool Game::game_turn()
{
    // Consistent changes
    if (this->game_maze->get_rounds_appeased() > 0)
    {
        this->game_maze->decrement_rounds_appeased();
    }

    // Get moves
    std::vector<char> special = this->game_maze->level_moves();

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
                check_logic = false; // Unrecognized user input, don't penalize
                break;

            case 'Q':
                return false;
                break;

            case 'R':
                this->game_maze->reset_curr_level();
                this->game_maze->set_rounds_appeased(0);
                student.take_skills();
                check_logic = false;
                break;

            case 'P':
                if (student.get_n_skills() > 0)
                {
                    student.use_skill();
                    this->game_maze->increment_rounds_appeased_by(10);
                }

                break;

            case 'U':
                int x = this->student.get_x_pos();
                int y = this->student.get_y_pos();
                OpenSpace * p_loc = static_cast<OpenSpace *>(
                                        this->game_maze->get_location(y, x));

                if (p_loc->get_has_end())
                {
                    this->game_maze->go_up_level();
                    this->game_maze->reset_curr_level();
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

        int x = this->student.get_x_pos();
        int y = this->student.get_y_pos();
        OpenSpace * p_loc = static_cast<OpenSpace *>(
                                this->game_maze->get_location(y, x));

        if (p_loc->get_has_p_skill() == true)
        {
            student.add_skill();
            p_loc->set_has_p_skill(false);
        }

        if (this->game_maze->check_intersection("IntrepidStudent", "TA", 1, false) == true)
        {
            ta_intersect = true;
        }

        if (this->game_maze->check_intersection("IntrepidStudent", "Instructor", 1, true) == true)
        {
            instructor_intersect = true;
        }


        // Handle these problems
        if (instructor_intersect == true)
        {
            display_maze();

            if (student.get_n_skills() >= 3)
            {
                std::cout << "You win! Press enter..." << std::endl;
                getchar();
                return false;
            }
            else
            {
                std::cout << "You don't have enough skill so you FAIL! Press enter..." << std::endl;
                getchar();
                this->game_maze->reset_to_start();
                this->game_maze->reset_curr_level();
                this->game_maze->set_rounds_appeased(0);
                student.take_skills();
            }
        }
        else if (ta_intersect == true)
        {
            if (this->game_maze->get_rounds_appeased() <= 0)
            {
                display_maze();

                std::cout << "You were terrified by a TA and lose all your skills! Press enter..." <<
                          std::endl;
                getchar();
                this->game_maze->reset_curr_level();
                student.take_skills();
            }
        }

    }

    display_maze();

    return true;
}

/*
 * Pre-condition:   Maze is setup and gameplay has begun, all fields instantiated
 */
void Game::display_maze()
{
    // Clear
    system("tput clear");

    // Display Maze
    if (show_hitboxes == true)
    {
        this->game_maze->display_level_ta();
    }
    else
    {
        this->game_maze->display_level();
    }

    std::cout << "Level     =  " << this->game_maze->get_curr_level() + 1
              << "/" << this->game_maze->get_n_levels() << std::endl;

    std::cout << "Skills    =  " << student.get_n_skills() << std::endl;

    std::cout << "Appeased  =  " << this->game_maze->get_rounds_appeased() << std::endl;
}


/*
 * Sets up the UI elements of the menu (MUST BE CALLED BEFORE MENUS ARE USED)
 */
void Game::setup_menu()
{
    /* main panel */
    // Title
    const char * title_str =
        " ___                         ___ ___   _  __ ___\n| __|_____ __ _ _ __  ___   / __/ __| / |/ /|_  )\n| _|(_-< _/ _` | '_ \\/ -_) | (__\\__ \\ | / _ \\/ /\n|___/__|__\\__,_| .__/\\___|  \\___|___/ |_\\___/___|\n               |_|\0";

    Panel * title_p = new Panel(0, 0, 57, 7, DYNAMIC_ELEMENT);
    Border * title_b = new Border('#', '=', '|', DYNAMIC_ELEMENT);
    Label * title_l = new Label(4, 1, " ", DYNAMIC_ELEMENT);
    title_l->set_str_cpy(title_str);
    title_p->add(title_l);
    title_p->add(title_b);

    // Contents
    const char * m_str =
        "~=# Main Menu #=~\n ...............\n\n  -(L)oad Game-\n\n   -(O)ptions-\n\n -(I)nformation-\n\n  -(Q)uit Game-\0";

    Panel * menu_c_p = new Panel(0, 6, 57, 14, DYNAMIC_ELEMENT);
    Border * menu_c_b = new Border('#', '`', '=', '|', '|', DYNAMIC_ELEMENT);
    Label * menu_c_l = new Label(20, 2, " ", DYNAMIC_ELEMENT);
    menu_c_l->set_str_cpy(m_str);
    menu_c_p->add(menu_c_l);
    menu_c_p->add(menu_c_b);

    // Panel
    Panel * main_menu_p = new Panel(0, 0, 57, 20, DYNAMIC_ELEMENT, "main");
    main_menu_p->add(menu_c_p);
    main_menu_p->add(title_p);
    /* end panel */


    /* options panel */
    const char * options_str =
        "        ~=# Options #=~\n\n            ---+---\n\n  (0) Show / Hide TA Hitboxes\n        current: [xxxx]\n\n(1) Shape / Size of TA Hitboxes\n        current: [xxxx]\n         (rect / plus)\n\n   (Q) Return to Main Menu\0";
    const char * show_str = (this->show_hitboxes) ? ("show") : ("hide");
    const char * hard_str = (this->hard_hitboxes) ? ("rect") : ("plus");

    Border * options_b = new Border('+', '-', '|', DYNAMIC_ELEMENT);
    Label * show_l = new Label(28, 7, " ", DYNAMIC_ELEMENT, "show");
    Label * hard_l = new Label(28, 10, " ", DYNAMIC_ELEMENT, "hard");
    Label * options_l = new Label(10, 2, " ", DYNAMIC_ELEMENT);
    show_l->set_str_cpy(show_str);
    hard_l->set_str_cpy(hard_str);
    options_l->set_str_cpy(options_str);

    Panel * options_p = new Panel(3, 2, 51, 16, DYNAMIC_ELEMENT, "options");
    options_p->add(options_l);
    options_p->add(options_b);
    options_p->add(show_l);
    options_p->add(hard_l);
    /* end panel */


    /* info panel */
    const char * info_str_a = "~=# Information 1/4 #=~\n\n        ---+---\0";
    const char * info_str_b = "(,) prev :: (.) next :: (Q) go back\0";
    this->info_pages[0] =
        "\n   In this game, your goal is to use (W,A,S,D)\n     guide the intrepid student ['S'] to the\n      ladder ['^'] at the end of each level\n          of the maze. climb using (U)!\0";
    this->info_pages[1] =
        "      While exploring, you'll be collecting\n  programming skills ['P'] along the way. These\n  will help you if and when you find the hidden\n   Instructor ['%'] on the highest tier of the\n    maze. Unless you have at least *3* skills\n     when you do, you will fail and restart!\0";
    this->info_pages[2] =
        "    These programming skills can also be used\n    on the way to fend off the terrifying TAs\n     wandering the maze. You can demonstrate\n       a skill with (P), losing one in the\n       process, but granting you 10 rounds\n       of invulnerability against the TAs.";
    this->info_pages[3] =
        "    If you have not used one of these skills\n     moving into any space adjacent to a TA\n     (excluding diagonal places by default)\n       you will lose all your held skills\n        and be sent back to the start of\n         the current level of the maze.\0";

    Border * info_b = new Border('+', '-', '|', DYNAMIC_ELEMENT);
    Label * info_l_a = new Label(14, 2, " ", DYNAMIC_ELEMENT);
    Label * info_l_b = new Label(8, 14, " ", DYNAMIC_ELEMENT);
    Label * info_l_c = new Label(1, 6, " ", DYNAMIC_ELEMENT, "info_list");
    Label * info_l_d = new Label(30, 2, "0", DYNAMIC_ELEMENT, "info_curr");
    Label * info_l_e = new Label(32, 2, "0", DYNAMIC_ELEMENT, "info_max");
    info_l_a->set_str_cpy(info_str_a);
    info_l_b->set_str_cpy(info_str_b);
    info_l_c->set_str_cpy(this->info_pages[0].c_str());

    Panel * info_p = new Panel(3, 2, 51, 16, DYNAMIC_ELEMENT, "info");
    info_p->add(info_l_a);
    info_p->add(info_l_b);
    info_p->add(info_l_c);
    info_p->add(info_l_d);
    info_p->add(info_l_e);
    info_p->add(info_b);
    /* end panel */


    /* load panel */
    const char * load_str_a = "~=# Load Game #=~\n\n     ---+---\0";
    const char * load_str_b =
        "                 Page - X/X\n(,) prev :: (.) next :: (R)efresh :: (Q) back\0";

    Border * load_b = new Border('+', '-', '|', DYNAMIC_ELEMENT);
    Label * load_l_a = new Label(17, 2, " ", DYNAMIC_ELEMENT);
    Label * load_l_b = new Label(3, 13, " ", DYNAMIC_ELEMENT);
    Label * load_l_c = new Label(27, 13, "0", DYNAMIC_ELEMENT, "load_curr");
    Label * load_l_d = new Label(29, 13, "0", DYNAMIC_ELEMENT, "load_max");
    Label * load_l_e = new Label(16, 6, "*No Maps Loaded*", DYNAMIC_ELEMENT, "load_list");
    load_l_a->set_str_cpy(load_str_a);
    load_l_b->set_str_cpy(load_str_b);

    Panel * load_p = new Panel(3, 2, 51, 16, DYNAMIC_ELEMENT, "load");
    load_p->add(load_l_a);
    load_p->add(load_l_b);
    load_p->add(load_l_c);
    load_p->add(load_l_d);
    load_p->add(load_l_e);
    load_p->add(load_b);
    /* end panel */


    /* set attributes */
    load_p->make_invisible();
    info_p->make_invisible();
    options_p->make_invisible();
    /* end attributes */


    /* window */
    this->menu_w = new Window(57, 20);

    this->menu_w->add(main_menu_p);
    this->menu_w->add(load_p);
    this->menu_w->add(info_p);
    this->menu_w->add(options_p);

    this->menu_w->open();
    this->menu_w->display();
    /* end window */
}


/*
 * Display the main menu and handles its logic (sending to other menus)
 * Pre-conditions:  setup_elements() has been called, game hasn't started.
 * Post-condition:  game is ready to play or it has been quit as shown by the
 *			maze_loaded field of the class.
 */
void Game::display_menu()
{
    bool menu_keep_going = true;

    while (menu_keep_going)
    {
        this->menu_w->display();

        char input = toupper(this->game_c.unbuffed_char_input());

        if (input == 'L')
        {
            load_menu(menu_keep_going);
        }
        else if (input == 'O')
        {
            options_menu();
        }
        else if (input == 'I')
        {
            info_menu();
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
}


/*
 * Displays the options menu and handles its logic.
 */
void Game::options_menu()
{
    this->menu_w->find("options")->make_visible();
    Label * show = static_cast<Label *>(this->menu_w->find("show"));
    Label * hard = static_cast<Label *>(this->menu_w->find("hard"));
    const char * show_str = (this->show_hitboxes) ? ("show") : ("hide");
    const char * hard_str = (this->hard_hitboxes) ? ("rect") : ("plus");
    show->set_str_cpy(show_str);
    hard->set_str_cpy(hard_str);

    bool settings_keep_going = true;

    while (settings_keep_going)
    {
        this->menu_w->display();

        char s_input = toupper(this->game_c.unbuffed_char_input());

        if (s_input == 'Q')
        {
            settings_keep_going = false;
        }
        else if (s_input == '0')
        {
            this->show_hitboxes = !this->show_hitboxes;
            show_str = (this->show_hitboxes) ? ("show") : ("hide");
            show->set_str_cpy(show_str);
        }
        else if (s_input == '1')
        {
            this->hard_hitboxes = !this->hard_hitboxes;
            hard_str = (this->hard_hitboxes) ? ("rect") : ("plus");
            hard->set_str_cpy(hard_str);
        }
    }

    this->menu_w->find("options")->make_invisible();
}


/*
 * Displays the maze loading menu and handles its logic.
 */
void Game::load_menu(bool & menu_keep_going)
{
    this->menu_w->find("load")->make_visible();
    Label * list_l = static_cast<Label *>(this->menu_w->find("load_list"));
    Label * curr_l = static_cast<Label *>(this->menu_w->find("load_curr"));
    Label * max_l = static_cast<Label *>(this->menu_w->find("load_max"));

    bool new_game_keep_going = true;
    int page_n = 0;

    list_l->set_str_cpy(this->load_pages[page_n].c_str());
    curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
    max_l->set_str_cpy(std::to_string(this->n_load_pages).c_str());

    while (new_game_keep_going)
    {
        this->menu_w->display();

        char m_input = toupper(this->game_c.unbuffed_char_input());

        if (m_input >= '0' && m_input <= '0' + this->load_list_max)
        {
            int choice = (m_input - '0') + (page_n * this->load_list_max);

            if (choice < this->map_files.size())
            {
                /* in bounds */
                new_game_keep_going = false;
                menu_keep_going = false;
                this->maze_loaded = true;
                this->chosen_map = this->map_files[choice];
            }
        }
        else if (m_input == ',')
        {
            if (page_n > 0)
            {
                page_n--;
                list_l->set_str_cpy(this->load_pages[page_n].c_str());
                curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
            }
        }
        else if (m_input == '.')
        {
            if (page_n < this->n_load_pages - 1)
            {
                page_n++;
                list_l->set_str_cpy(this->load_pages[page_n].c_str());
                curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
            }
        }
        else if (m_input == 'R')
        {
            page_n = 0;
            fill_load_pages();
            list_l->set_str_cpy(this->load_pages[page_n].c_str());
            curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
            max_l->set_str_cpy(std::to_string(this->n_info_pages).c_str());
        }
        else if (m_input == 'Q')
        {
            new_game_keep_going = false;
        }
    }

    this->menu_w->find("load")->make_invisible();
}


/*
 * Displays the maze information menu and handles its logic.
 */
void Game::info_menu()
{
    this->menu_w->find("info")->make_visible();
    Label * list_l = static_cast<Label *>(this->menu_w->find("info_list"));
    Label * curr_l = static_cast<Label *>(this->menu_w->find("info_curr"));
    Label * max_l = static_cast<Label *>(this->menu_w->find("info_max"));

    bool info_keep_going = true;
    int page_n = 0;

    list_l->set_str_cpy(this->info_pages[page_n].c_str());
    curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
    max_l->set_str_cpy(std::to_string(this->n_info_pages).c_str());

    while (info_keep_going)
    {
        this->menu_w->display();

        char m_input = toupper(this->game_c.unbuffed_char_input());

        if (m_input == ',')
        {
            if (page_n > 0)
            {
                page_n--;
                list_l->set_str_cpy(this->info_pages[page_n].c_str());
                curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
            }
        }
        else if (m_input == '.')
        {
            if (page_n < this->n_info_pages - 1)
            {
                page_n++;
                list_l->set_str_cpy(this->info_pages[page_n].c_str());
                curr_l->set_str_cpy(std::to_string(page_n + 1).c_str());
            }
        }
        else if (m_input == 'Q')
        {
            info_keep_going = false;
        }
    }

    this->menu_w->find("info")->make_invisible();
}
