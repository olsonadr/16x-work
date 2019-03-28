/*
 *  Program:		Game.cpp - Game Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Game class described in
 *                      Game.hpp, objects of which represent the Game and
 *                      all of its logic and UI. This is the interface
 *                      with which the basic gameplay flow can be started
 *                      and ended.
 */

#include "Game.hpp"

/*                                                                                      -
 * Constructor:		Game::Game()
 * Description:		Primary constructor of the Game class, sets fields, allocates me-
 *			    mory, and generates the map using the passed cave dimensions.
 *			    Also enforces that the dimensions are within the required ra-
 *			    nge of [4,12].
 * Parameters:		int cave_w:
 *			    The desired width (cols) of the cave.
 *			int cave_h:
 *			    The disired height (rows) of the cave.
 * Pre-conditions:	No fields have been instantiated.
 * Post-conditions:     All have been instantiated (some during the generate_map() call)
 */
Game::Game(int cave_w, int cave_h)
    : cave_width(0), cave_height(0),
      p(new Player()),
      init_wump_room(nullptr),
      init_gold_room(nullptr),
      exit_x(0), exit_y(0)
{
    if (cave_w < 4)
    {
        cave_w = 4;
    }
    else if (cave_w > 12)
    {
        cave_w = 12;
    }

    if (cave_h < 4)
    {
        cave_h = 4;
    }
    else if (cave_h > 12)
    {
        cave_h = 12;
    }

    srand(time(NULL));
    generate_map(cave_w, cave_h);
}


/*                                                                                      -
 * Destructor:		Game::~Game()
 * Description:		Deallocates all memory this Game has allocated.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:     All memory has been freed (using the generate_map() function that
 *			    clears and deletes all rooms when resizing down).
 */
Game::~Game()
{
    generate_map(0, 0);
    delete this->p;
}


/*                                                                                      -
 * Function:		Game::generate_map_str()
 * Description:		Fills the passed char buffers with the string representations of
 *			    the Rooms of the cave and the Player due to the cave's dime-
 *			    nsions. Also stores the appropriate values of the width and
 *			    height of each room, the position offsets of the Player str-
 *			    ing relative to the top corner of each room, and the position
 *			    of the top-left corner of the cave string buffer. Should be
 *			    called only when the Game is being setup or the dimensions of
 *			    the cave have changed (shouldn't happen in current version of
 *			    the game).
 * Parameters:		char *& rooms_str:
 *			    The char buffer for the cave's Rooms' string representation.
 *			char *& player_str:
 *			    The char buffer for the Player's icon string representation.
 * Pre-Conditions:	rooms_str and player_str are allocated and ready to be filled.
 *			    With current version of game, rooms_str will always be 1500
 *			    or more chars long, and player_str will be 30 or more.
 * Post-Conditions:	room_w, room_h, p_l_x_off, p_l_y_off, cave_str_x, and cave_str_y
 *			    have all been instantiated for the current width and height
 *			    of the cave.
 */
void Game::generate_map_str(char *& rooms_str,
                            char *& player_str)
{
    // Scale UI elements to cave size
    if (this->cave_width >= 11)
    {
        this->room_w = 3;
        this->room_h = 1;
        this->p_l_x_off = 2;
        this->p_l_y_off = 1;
        this->cave_str_x = 2 + (4 - 2 * (this->cave_width % 11));
        this->cave_str_y = 0 + (1 - this->cave_height % 11);

        sprintf(player_str, "X\0");
    }
    else if (this->cave_width >= 8)
    {
        this->room_w = 4;
        this->room_h = 1;
        this->p_l_x_off = 2;
        this->p_l_y_off = 1;
        this->cave_str_x = 3 + (5 - 2.5 * (this->cave_width % 8));
        this->cave_str_y = 2 + (2 - this->cave_height % 8);

        sprintf(player_str, "><\0");
    }
    else if (this->cave_width >= 7)
    {
        this->room_w = 6;
        this->room_h = 2;
        this->p_l_x_off = 3;
        this->p_l_y_off = 1;
        this->cave_str_x = 3;
        this->cave_str_y = 1;

        sprintf(player_str, "\\/\n/\\\0");
    }
    else if (this->cave_width >= 6)
    {
        this->room_w = 8;
        this->room_h = 3;
        this->p_l_x_off = 3;
        this->p_l_y_off = 1;
        this->cave_str_x = 1;
        this->cave_str_y = 0;

        sprintf(player_str, "\\  /\n XX\n/  \\\0");
    }
    else if (this->cave_width >= 5)
    {
        this->room_w = 9;
        this->room_h = 3;
        this->p_l_x_off = 4;
        this->p_l_y_off = 1;
        this->cave_str_x = 3;
        this->cave_str_y = 2;

        sprintf(player_str, "\\ /\n X\n/ \\\0");
    }
    else
    {
        this->room_w = 11;
        this->room_h = 5;
        this->p_l_x_off = 4;
        this->p_l_y_off = 1;
        this->cave_str_x = 4;
        this->cave_str_y = 0;

        sprintf(player_str, "\\   /\n \\ /\n  X\n / \\\n/   \\\0");
    }

    // Format room layout for space
    int row_max = this->cave_height * (this->room_h + 1) + 1;
    int col_max = this->cave_width * (this->room_w + 1) + 1;

    for (int row = 0; row < row_max; row++)
    {
        bool is_top = (row % (this->room_h + 1) == 0) || (row == row_max - 1);
        int str_i = row * (col_max + 1);

        for (int col = 0; col < col_max; col++)
        {
            bool is_side = (col % (this->room_w + 1) == 0) || (col == col_max - 1);

            if (is_top == true &&
                    is_side == true)
            {
                rooms_str[str_i + col] = '+';
            }
            else if (is_top == true)
            {
                rooms_str[str_i + col] = '-';
            }
            else if (is_side == true)
            {
                rooms_str[str_i + col] = '|';
            }
            else
            {
                rooms_str[str_i + col] = ' ';
            }
        }

        rooms_str[str_i + col_max] = (row < row_max - 1) ? ('\n') : ('\0');
    }
}


/*                                                                                      -
 * Function:		Game::setup()
 * Description:		Sets up and opens the UI of the Game using my cpp_panels library.
 *			    Should only be called once for the Game, although it could be
 *			    called more than once if you want to have huge memory leaks.
 *			    Uses the generate_map_str() function to format the Labels for
 *			    the cave and Player. Long by necessity but makes things fast-
 *			    er in the future, just trust me. Calls enter_room() before
 *			    ending, so the starting Room's adjacent percepts are listed.
 * Pre-conditions:	All fields have been instantiated. This is the first time this is
 *			    being called for this Game (please).
 * Post-conditions:	The UI has been compiled and opened, let the Game begin!
 */
void Game::setup()
{
    /* cpp_panels UI setup */
    /* Window stuff */
    int window_w = 92, window_h = 36;
    this->game_window = new Window(window_w, window_h);
    Border * window_border = new Border('#', '=', '|', DYNAMIC_ELEMENT);


    /* Header stuff */
    int header_height = 8;

    const char * title_str =
        "                    _     _   _            __    __\n  /\\  /\\_   _ _ __ | |_  | |_| |__   ___  / / /\\ \\ \\_   _ _ __ ___  _ __  _   _ ___\n / /_/ / | | | '_ \\| __| | __| '_ \\ / _ \\ \\ \\/  \\/ / | | | '_ ` _ \\| '_ \\| | | / __|\n/ __  /| |_| | | | | |_  | |_| | | |  __/  \\  /\\  /| |_| | | | | | | |_) | |_| \\__ \\\n\\/ /_/  \\__,_|_| |_|\\__|  \\__|_| |_|\\___|   \\/  \\/  \\__,_|_| |_| |_| .__/ \\__,_|___/\n                                                                   |_|\0";

    Panel * header_panel = new Panel(0, 0, window_w, header_height, DYNAMIC_ELEMENT);
    Border * header_border = new Border('#', '=', '`', DYNAMIC_ELEMENT);
    Label * game_title = new Label(4, 1, " ", DYNAMIC_ELEMENT);
    game_title->set_str_cpy(title_str);

    header_panel->set_bg_char('`');
    header_panel->add(game_title);
    header_panel->add(header_border);
    /* End header stuff, header_panel is compiled */


    /* Sidebar list (objectives, backpack, console) */
    // Sidebar
    int sidebar_width = 34;

    Border * sidebar_border = new Border('`', '`', '|', DYNAMIC_ELEMENT);

    List * sidebar_list = new List(window_w - sidebar_width,
                                   header_height - 1, sidebar_width,
                                   DYNAMIC_ELEMENT, VERTICAL_LIST);

    sidebar_list->set_margins(1);
    sidebar_list->set_bg_char('`');
    sidebar_list->add(sidebar_border);

    // Objectives
    const char * objectives_str =
        "Objectives:\n  [ ] - Kill the evil Wumpus\n  [ ] - Steal the Gold hoard\0";
    const char * check_str = "X\0";

    this->wumpus_check_label = new Label(5, 2, " ", DYNAMIC_ELEMENT);
    this->wumpus_check_label->set_str_cpy(check_str);
    this->wumpus_check_label->make_invisible();

    this->gold_check_label = new Label(5, 3, " ", DYNAMIC_ELEMENT);
    this->gold_check_label->set_str_cpy(check_str);
    this->gold_check_label->make_invisible();

    Label * objectives_l = new Label(2, 1, " ", DYNAMIC_ELEMENT);
    objectives_l->set_str_cpy(objectives_str);

    Panel * objectives_p = new Panel(0, 0, sidebar_width - 2, 5, DYNAMIC_ELEMENT);
    objectives_p->add(objectives_l);
    objectives_p->add(wumpus_check_label);
    objectives_p->add(gold_check_label);

    // Backpack
    const char * backpack_str = "Backpack:           # Arrows\0";
    char num_arrows_str[3];
    sprintf(num_arrows_str, "%d\0", this->p->get_n_arrows());

    this->num_arrows_label = new Label(22, 1, " ", DYNAMIC_ELEMENT);
    this->num_arrows_label->set_str_cpy(num_arrows_str);

    Label * backpack_l = new Label(2, 1, " ", DYNAMIC_ELEMENT);
    backpack_l->set_str_cpy(backpack_str);

    Panel * backpack_p = new Panel(0, 0, sidebar_width - 2, 3, DYNAMIC_ELEMENT);
    backpack_p->add(backpack_l);
    backpack_p->add(this->num_arrows_label);

    // Delimeter
    const char * delimeter = "--------------------------------\0";
    Label * delimeter_l_1 = new Label(0, 0, " ", DYNAMIC_ELEMENT);
    Label * delimeter_l_2 = new Label(0, 0, " ", DYNAMIC_ELEMENT);
    delimeter_l_1->set_str_cpy(delimeter);
    delimeter_l_2->set_str_cpy(delimeter);

    // Console
    int max_history = 15;
    int console_p_width = sidebar_width - 2, console_p_height = 16;

    this->game_console = new Console(2, 1, console_p_width - 4,
                                     console_p_height - 3,
                                     max_history, DYNAMIC_ELEMENT,
                                     "wumpus-console");

    this->game_console->set_display_input_line(false);

    Panel * console_p = new Panel(0, 0, console_p_width,
                                  console_p_height, DYNAMIC_ELEMENT);

    console_p->add(this->game_console);

    // Putting sidebar together
    sidebar_list->add(objectives_p);
    sidebar_list->add(delimeter_l_1);
    sidebar_list->add(backpack_p);
    sidebar_list->add(delimeter_l_2);
    sidebar_list->add(console_p);
    sidebar_list->update();
    /* End sidebar list */


    /* Cave panel */
    char * cave_str = new char[1500];
    char * player_str = new char[30];
    generate_map_str(cave_str, player_str);
    int cave_p_width = 56, cave_p_height = 25;

    // Player Label
    this->player_label = new Label(0, 0, " ", DYNAMIC_ELEMENT);
    player_label->set_str_cpy(player_str);
    update_p_str_pos();
    delete[] player_str;

    // Cave Label
    Label * cave_l = new Label(this->cave_str_x, this->cave_str_y,
                               " ", DYNAMIC_ELEMENT);
    cave_l->set_str_cpy(cave_str);
    delete[] cave_str;

    // Cave Panel
    Panel * cave_p = new Panel(1, header_height,
                               cave_p_width, cave_p_height,
                               DYNAMIC_ELEMENT);

    // Putting Cave Together
    cave_p->add(cave_l);
    cave_p->add(this->player_label);
    /* End cave panel */


    /* Controls panel */
    const char * controls_str =
        "Ctrls: | (w,a,s,d) - move (N,W,S,E)  |  <shift>+(w,a,s,d) - shoot (N,W,S,E)  |  q - quit\0";

    Panel * controls_p = new Panel(0, window_h - 3, window_w, 3, DYNAMIC_ELEMENT);
    Border * controls_b = new Border('#', '-', '`', '`', '`', DYNAMIC_ELEMENT);
    Label * controls_l = new Label(2, 1, " ", DYNAMIC_ELEMENT);
    controls_l->set_str_cpy(controls_str);

    // Putting controls together
    controls_p->add(controls_b);
    controls_p->add(controls_l);
    controls_p->set_bg_char('`');
    /* End controls panel */


    /* Alert box */
    this->general_alert = new Alert(" ", DYNAMIC_ELEMENT);
    Border * alert_border = new Border('x', '~', '~', '|', '|', DYNAMIC_ELEMENT);

    this->general_alert->set_size_percentage(.82);
    this->general_alert->set_border(alert_border);
    /* End alert box */


    // Putting window together
    this->game_window->add(window_border); /* Very bottom */
    this->game_window->add(header_panel);
    this->game_window->add(cave_p);
    this->game_window->add(sidebar_list);
    this->game_window->add(controls_p);
    this->game_window->add(general_alert);


    /* Console setup */
    this->game_console->setup_input(
        this->game_window->find_global_pos(
            "wumpus-console"));
    /* End console setup */


    /* End cpp_panels UI setup */


    // Open and Display!
    this->game_window->open();
    this->game_window->unsafe_clear();
    enter_room();
    this->game_window->display();
}


/*                                                                                      -
 * Function:		Game::update_p_str_pos()
 * Description:		Sets the position of the Player's icon Label to the correct posi-
 *			    tion due to this cave's dimensions.
 * Pre-Conditions:	All fields instantiated, setup() has been called.
 * Post-Conditions:	The player's Label has been moved to correct position.
 */
void Game::update_p_str_pos()
{
    int p_x = this->cave_str_x
              + (this->p->get_x_pos() * (this->room_w + 1))
              + this->p_l_x_off;

    int p_y = this->cave_str_y
              + (this->p->get_y_pos() * (this->room_h + 1))
              + this->p_l_y_off;

    this->player_label->set_pos(p_x, p_y);
}


/*                                                                                      -
 * Function:		Game::cleanup()
 * Description:		Cleans up the Game's UI stuff, deleting the Window, which should
 *			    in turn handle all memory of its members. Must be called be-
 *			    fore the Game is destructed, if setup() has been called.
 * Pre-conditions:	All fields have been instantiated, the UI is ready to be closed.
 * Post-conditions:	The Window has been closed and its memory has been deallocated.
 */
void Game::cleanup()
{
    game_window->unsafe_clear();
    game_window->close();
    delete this->game_window;
}


/*                                                                                      -
 * Function:		Game::update_ui()
 * Description:		Updates all the cpp_panels aspects of the program to correctly
 *			    display current state of the game (indicators, number of arr-
 *			    ows, etc.
 * Pre-Conditions:	All fields instantiated. UI is setup.
 * Post-Conditions:	UI elements updated.
 */
void Game::update_ui()
{
    // Player label
    update_p_str_pos();

    // Objectives checkmarks
    if (this->p->get_has_killed_wumpus() != this->wumpus_check_label->get_is_visible())
    {
        this->wumpus_check_label->toggle_visible();
    }

    if (this->p->get_has_gold() != this->gold_check_label->get_is_visible())
    {
        this->gold_check_label->toggle_visible();
    }

    // Number of arrows
    char buff[3];
    sprintf(buff, "%d\0", this->p->get_n_arrows());
    this->num_arrows_label->set_str_cpy(buff);
}


/*                                                                                      -
 * Function:		Game::generate_percepts()
 * Description:		Generates and outputs the percepts for the Rooms around the Pla-
 *			    yer's current Room.
 * Pre-Conditions:	All fields instantiated. Cave dimensions are accurate.
 * Post-Conditions:	The percepts due to the surrounding rooms have been outputted.
 */
void Game::generate_percepts()
{
    bool any_found = false;
    output("\n#=~\nFrom this room:");

    int p_x = this->p->get_x_pos();
    int p_y = this->p->get_y_pos();

    // Room to North
    if (p_y - 1 >= 0)
    {
        if (this->rooms[p_y - 1][p_x]->get_has_event() == true)
        {
            output(this->rooms[p_y - 1][p_x]->get_percept());
            any_found = true;
        }
    }

    // Room to South
    if (p_y + 1 < this->cave_height)
    {
        if (this->rooms[p_y + 1][p_x]->get_has_event() == true)
        {
            output(this->rooms[p_y + 1][p_x]->get_percept());
            any_found = true;
        }
    }

    // Room to West
    if (p_x - 1 >= 0)
    {
        if (this->rooms[p_y][p_x - 1]->get_has_event() == true)
        {
            output(this->rooms[p_y][p_x - 1]->get_percept());
            any_found = true;
        }
    }

    // Room to East
    if (p_x + 1 < this->cave_width)
    {
        if (this->rooms[p_y][p_x + 1]->get_has_event() == true)
        {
            output(this->rooms[p_y][p_x + 1]->get_percept());
            any_found = true;
        }
    }

    if (any_found == true)
    {
        output("#=~");
    }
    else
    {
        output("You observe nothing...\n#=~");
    }

    this->game_window->display();
}


/*                                                                                      -
 * Function:		Game::generate_map()
 * Description:		Generates the cave's rooms array, allocating and deallocating
 *			    Rooms as needed if this is a resize rather than the first
 *			    creation, allowing it to be used for deletion of all Room
 *			    memory. Clears all the Rooms' Events, so calling this and
 *			    passing the same dimensions will randomize Event positions.
 * Parameters:		int new_width:
 *			    The desired width (cols) of the cave.
 *			int new_height:
 *			    The desired height (rows) of the cave.
 * Pre-conditions:	The map must be generated. new_width and new_height must be grea-
 *			    ter than 0 in all cases. This is called when the program sta-
 *			    rts but also when the user wants to regenerate with new dims
 *			    or with new Event positions.
 * Post-conditions:	The map has been generated and Events have been positioned rando-
 *			    mly. Memory is allocated here, but is de-allocated in the ro-
 *			    oms, so don't worry about it.
 */
void Game::generate_map(int new_width, int new_height)
{
    // Reset all currently allocated rooms to having no Event.
    for (int row = 0; row < this->cave_height; row++)
    {
        for (int col = 0; col < this->cave_width; col++)
        {
            this->rooms[row][col]->clear_event();
        }
    }

    // Grow or shrink as needed
    if (new_width < this->cave_width ||
            new_height < this->cave_height)
    {
        /* Must deallocate old Rooms */

        // Deallocate first
        for (int row = 0; row < this->cave_height; row++)
        {
            for (int col = 0; col < this->cave_width; col++)
            {
                if (row >= new_height ||
                        col >= new_width)
                {
                    /* The area outside the new dims */
                    delete this->rooms[row][col];
                }
            }
        }

        // Then resize
        this->rooms.resize(new_height);

        for (int i = 0; i < new_height; i++)
        {
            this->rooms[i].resize(new_width);
        }
    }
    else if (new_width > this->cave_width ||
             new_height > this->cave_height)
    {
        /* Must allocate new Rooms */

        // Resize first
        this->rooms.resize(new_height);

        for (int i = 0; i < new_height; i++)
        {
            this->rooms[i].resize(new_width);
        }

        // Then allocate new Rooms
        for (int row = 0; row < new_height; row++)
        {
            for (int col = 0; col < new_width; col++)
            {
                if (row >= this->cave_height ||
                        col >= this->cave_width)
                {
                    /* The area outside the old dims */
                    this->rooms[row][col] = new Room();
                }
            }
        }
    }

    // Assign these new dimensions as they are now accurate
    this->cave_width = new_width;
    this->cave_height = new_height;

    if (this->cave_width >= 4 &&
            this->cave_height >= 4)
    {
        // Create Events (allowing for variable nums) and assign them to random rooms
        int num_bats = 2, num_pits = 2, num_wumpi = 1, num_gold = 1;

        for (int i = 0; i < num_bats; i++)
        {
            Bats * new_bat = new Bats(this->cave_width,
                                      this->cave_height);

            add_to_rand_empty_room(new_bat);
        }

        for (int i = 0; i < num_pits; i++)
        {
            Pit * new_pit = new Pit();
            add_to_rand_empty_room(new_pit);
        }

        for (int i = 0; i < num_wumpi; i++)
        {
            Wumpus * new_wumpus = new Wumpus();
            this->init_wump_room = add_to_rand_empty_room(new_wumpus);
        }

        for (int i = 0; i < num_gold; i++)
        {
            Gold * new_gold = new Gold();
            this->init_gold_room = add_to_rand_empty_room(new_gold);
        }
    }

    // Set new dimensions as the Player understands them
    move_p_to_rand_empty_room();
    this->p->set_dims(this->cave_width, this->cave_height);

    // Finish!
}


/*                                                                                      -
 * Function:		Game::add_to_rand_empty_room()
 * Description:		Adds the passed event to a random empty Room in this Game's rooms
 *			    array, giving up if it can't do so within max_failures tries,
 *			    which is currently at 200. This is to stop infinite loops if
 *			    the code is modified to add more Events than there are total
 *			    Rooms in the cave.
 * Parameters:		Event * to_add:
 *			    A pointer to the Event that should be added to a Room.
 * Return Value:	A pointer to the Room the Event was added to, nullptr if a Room
 *			    wasn't found within max_failures tries.
 * Pre-Conditions:	All fields instantiated. The row_gen and col_gen parameters are
 *			    accurate to the currently allocated Room grid.
 * Post-Conditions:	Has added the passed event to a random available room if it finds
 *			    an available room in the first 'max_failures' tries listed in
 *			    the body of the function. Returns the pointer to the Room it
 *			    was placed into or nullptr if an empty room wasn't found.
 */
Room * Game::add_to_rand_empty_room(Event * to_add)
{
    int failures = 0, max_failures = 200;
    int rand_row, rand_col;
    Room * rand_room = nullptr;
    bool keep_going = true;

    while (keep_going == true &&
            failures < max_failures)
    {
        rand_row = rand() % this->cave_height;
        rand_col = rand() % this->cave_width;
        rand_room = this->rooms[rand_row][rand_col];

        if (rand_room->get_has_event() == false)
        {
            /* the random room is empty */
            rand_room->set_event(to_add);
            keep_going = false;
        }
        else
        {
            /* the random room already had an event */
            failures++;
        }
    }

    return rand_room;
}


/*                                                                                      -
 * Function:		Game::move_p_to_rand_empty_room()
 * Description:		Moves the Player to a random empty Room in the cave, giving up
 *			    after max_failures tries if the code is something goes hor-
 *			    ribly wrong.
 * Pre-Conditions:	All fields instantiated. Cave height and width are accurate.
 * Post-Conditions:	Has moved the player to a random available room if it finds an
 *			    available room in the first 'max_failures' tries listed in
 *			    the body of the function.
 */
void Game::move_p_to_rand_empty_room()
{
    int failures = 0, max_failures = 200;
    int rand_row, rand_col;
    bool keep_going = true;

    if (this->cave_width > 0 &&
            this->cave_height > 0)
    {
        while (keep_going == true &&
                failures < max_failures)
        {
            rand_row = rand() % this->cave_height;
            rand_col = rand() % this->cave_width;

            Room * rand_room = this->rooms[rand_row][rand_col];

            if (rand_room->get_has_event() == false)
            {
                /* the random room is empty */
                this->p->move_to(rand_col, rand_row);
                this->exit_x = rand_col;
                this->exit_y = rand_row;
                keep_going = false;
            }
            else
            {
                /* the random room already had an event */
                failures++;
            }
        }
    }
}


/*                                                                                      -
 * Function:		Game::handle_input()
 * Description:		Gets (using get_char_input()) and handles user input, moving or
 *			    shooting, etc. Returns whether the Game is now over due to
 *			    this input.
 * Returns:		Whether the Game is lost because of this action as a bool.
 * Pre-Conditions:	All fields instantiated. UI is setup().
 * Post-Conditions:	The input has been handled, whether the Game is over is returned.
 */
bool Game::handle_input()
{
    std::string input = get_char_input();

    if (input == "w")
    {
        this->p->move("N");
        update_ui();
        this->game_window->display();
        return enter_room();
    }

    else if (input == "s")
    {
        this->p->move("S");
        update_ui();
        this->game_window->display();
        return enter_room();
    }

    else if (input == "a")
    {
        this->p->move("W");
        update_ui();
        this->game_window->display();
        return enter_room();
    }

    else if (input == "d")
    {
        this->p->move("E");
        update_ui();
        this->game_window->display();
        return enter_room();
    }

    else if (input == "W")
    {
        return shoot_arrow("N");
    }

    else if (input == "S")
    {
        return shoot_arrow("S");
    }

    else if (input == "A")
    {
        return shoot_arrow("W");
    }

    else if (input == "D")
    {
        return shoot_arrow("E");
    }
    else if (input == "q" ||
             input == "Q")
    {
        const char * message =
            "Do you reeeeaaallly want to quit?\n   The journey has just begun!\n           (y) or (n)\0";
        this->general_alert->set_message(message);
        this->general_alert->make_visible();
        this->game_window->display();
        std::string input;

        while (input != "y" && input != "n")
        {
            input = get_char_input();
        }

        this->general_alert->make_invisible();
        this->game_window->display();

        if (input == "y")
        {
            return GAME_IS_OVER;
        }
        else
        {
            return GAME_NOT_OVER;
        }
    }
    else
    {
        /* Unrecognized Input */
        return GAME_NOT_OVER;
    }
}


/*                                                                                      -
 * Function:		Game::shoot_arrow()
 * Description:		Shoots an arrow in the passed direction, handling whether this
 *			    kils the Wumpus, whether the Wumpus is missed and moves,
 *			    whether the Player missing entails a Game over, etc.
 * Parameters:		std::string direction:
 *			    The direction to move as a string (N, S, E, W for up, down,
 *			    right, left, respectively).
 * Returns:		Whether the Game is over because this arrow was shot as bool.
 * Pre-Conditions:	All fields instantiated.
 * Post-Conditions:	The effects of the shot of this arrow have been handled, whether
 *			    the Game is over because of it has been returned.
 */
bool Game::shoot_arrow(std::string direction)
{
    if (this->p->get_n_arrows() > 0)
    {
        this->p->shoot(); // Decrements n_arrows.

        update_ui();
        this->game_window->display();

        int x_start = this->p->get_x_pos();
        int y_start = this->p->get_y_pos();
        bool keep_going = true;
        int distance = 0;

        while (keep_going &&
                distance < 3)
        {
            Room * curr_room = nullptr;

            if (direction == "N")
            {
                if (y_start - distance >= 0)
                {
                    curr_room = this->rooms[y_start - distance][x_start];
                }

            }
            else if (direction == "S")
            {
                if (y_start + distance < this->cave_height)
                {
                    curr_room = this->rooms[y_start + distance][x_start];
                }

            }
            else if (direction == "W")
            {
                if (x_start - distance >= 0)
                {
                    curr_room = this->rooms[y_start][x_start - distance];
                }

            }
            else if (direction == "E")
            {
                if (x_start + distance < cave_width)
                {
                    curr_room = this->rooms[y_start][x_start + distance];
                }

            }

            if (curr_room != nullptr &&
                    curr_room->has_wumpus() == true)
            {
                this->p->set_has_killed_wumpus(true);
                curr_room->clear_event();
                update_ui();
                output("\n#=~\nYou've killed the Wumpus!\n#=~");
                this->game_window->display();
                keep_going = false;
            }

            distance++;
        }

        if (keep_going == true &&
                this->p->get_has_killed_wumpus() == false)
        {
            /* The shot missed and Wumpus is still alive */
            if (this->p->get_n_arrows() <= 0)
            {
                /* The Player ran out of arrows and failed */
                alert_and_pause("You ran out of arrows before killing the Wumpus!\n Press enter...");
                return GAME_IS_OVER;
            }

            output("\n#=~\nYou missed the Wumpus.\nIt may have moved...\n#=~");
            int rand_num = rand() % 4;

            if (rand_num > 0)
            {
                /* 75% chance, Wumpus moves */
                Wumpus * new_wumpus = new Wumpus;
                find_wumpus_room()->clear_event();
                add_to_rand_empty_room(new_wumpus);
            }
        }
    }

    return GAME_NOT_OVER;
}


/*                                                                                      -
 * Function:		Game::enter_room()
 * Description:		Handles the effects of the Player entering the Room at the posi-
 *			    tion the Player currently reports, mostly meaning the affec-
 *			    ts of the Room's Event, updating the UI, and generating the
 *			    percepts the Player should see after it was all handled.
 * Returns:		Whether the Game is over because this room was entered or not.
 * Pre-Conditions:	All Rooms are initialized, the Player position is accurate.
 * Post-Conditions:	The Player has been affected as it should by the Event of the
 *			    current Room the Player is in.
 */
bool Game::enter_room()
{
    Room * curr_room = this->rooms[this->p->get_y_pos()][this->p->get_x_pos()];

    // See how it affects the Player and store result
    bool result = curr_room->handle_player(this->p);

    // Display alert appropriate to this Room
    if (curr_room->get_has_event() == true)
    {
        /* The Room has an Event, should Alert about something */
        alert_and_pause(curr_room->get_enter_text());

        // Update UI as needed
        update_ui();
        this->game_window->display();
    }

    // Effects of specific rooms that aren't handled by their handle_player() function
    if (curr_room->get_event_name() == "Gold")
    {
        this->init_gold_room->clear_event();
    }
    else if (curr_room->get_event_name() == "Super Bats")
    {
        // The Player has been moved, check new room
        result = enter_room();
    }
    else if (this->p->get_y_pos() == this->exit_y &&
             this->p->get_x_pos() == this->exit_x)
    {
        /* This is the exit */
        if (this->p->get_has_gold() == true &&
                this->p->get_has_killed_wumpus() == true)
        {
            /* They've met the conditions to win */
            alert_and_pause("         Congratulations!           \n\n   You killed the horrid Wumpus,    \n  found the hidden hoard of gold,  \n    and escaped with your life!     \n\n You are truly a hero for the ages! \n\n           Press enter...");
            result = GAME_IS_OVER;
        }
        else
        {
            // Tell user they found exit but haven't met the conditions
            output("\nThis room has the exit,\nbut you haven't completed\nyour quest!");
            this->game_window->display();
            result = GAME_NOT_OVER;
        }
    }

    /* Generate percepts and print them */
    generate_percepts();

    return result;
}


/*
 * Prints the contents of the cave (map), used for debug, shows Events, must be generated.
 * Not used in the Game currently; debug function.
 */
void Game::print_map()
{
    printf("\n");

    for (int row = 0; row < this->cave_height; row++)
    {
        printf("|");

        for (int col = 0; col < this->cave_width; col++)
        {
            if (this->p->get_x_pos() == col &&
                    this->p->get_y_pos() == row)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << " ";
            }

            std::cout << std::setw(14) << std::left
                      << this->rooms[row][col]->get_event_name()
                      << " |";
        }

        printf("\n");
    }
}


/*                                                                                      -
 * Function:		Game::alert_and_pause()
 * Description:		Alerts the player of some message (using UI hopefully).
 * Parameters:		std::string message:
 *			    The message to be communicated to the player.
 * Pre-Conditions:	All fields instantiated.
 * Post-Conditions:	The user has been alerted and they have hit enter to proceed.
 */
void Game::alert_and_pause(std::string message)
{
    this->general_alert->set_message(message.c_str());
    this->general_alert->make_visible();
    this->game_window->display();
    this->game_console->pause_and_flush();
    this->general_alert->make_invisible();
    this->game_window->display();
}


/*                                                                                      -
 * Function:		Game::output()
 * Description:		The output function that relays information to the user
 * Parameters:		std::string message:
 *			    The first argument passed.
 * Pre-Conditions:	The arguments are strings.
 * Post-Conditions:	The arguments have all been printed.
 */
void Game::output(std::string message)
{
    this->game_console->output(message.c_str());
}


/*                                                                                      -
 * Function:		Game::input()
 * Description:		Takes user input after output()-ing a passed prompt string.
 * Parameters:		std::string prompt:
 *			    The prompt for the user before getting their input.
 * Return Value:	The user's response as an std::string.
 * Post-Conditions:	The user's input has been returned.
 */
std::string Game::input(std::string prompt)
{
    // Prompt
    if (prompt != "")
    {
        output(prompt.c_str());
    }

    // Setup Console
    this->game_console->set_display_input_line(true);
    this->game_window->display();

    // Get and Store Input
    char input_buff[MAX_INPUT_LENGTH];
    this->game_console->input(input_buff, MAX_INPUT_LENGTH);
    std::string result = input_buff;

    // Cleanup
    this->game_console->set_display_input_line(false);
    this->game_window->display();

    // Return
    return result;
}


/*                                                                                      -
 * Function:		Game::get_char_input()
 * Description:		Takes user unbuffered input after output()-ing a passed prompt
 *			    string, not waiting for an enter press.
 * Parameters:		std::string prompt:
 *			    The prompt for the user before getting their input.
 * Return Value:	The user's response as an std::string.
 * Post-Conditions:	The user's input has been returned.
 */
std::string Game::get_char_input(std::string prompt)
{
    // Prompt
    if (prompt != "")
    {
        output(prompt.c_str());
    }

    // Get input
    std::string result = " ";
    result[0] = this->game_console->unbuffed_char_input();

    // Return input
    return result;
}


/*                                                                                      -
 * Function:		Game::find_wumpus_room()
 * Description:		Determines which Room in the cave contains the Wumpus, returns a
 *			    pointer to this Room if the Wumpus is found, nullptr if not.
 * Return Value:	The Room pointer for the Room in the cave with the Wumpus, else,
 *			    if it wasn't found, nullptr.
 * Pre-Conditions:	All fields instantiated. Map has been generated.
 * Post-Conditions:	The Room containing the Wumpus or nullptr has been returned.
 */
Room * Game::find_wumpus_room()
{
    for (int row = 0; row < this->cave_height; row++)
    {
        for (int col = 0; col < this->cave_width; col++)
        {
            if (this->rooms[row][col]->has_wumpus() == true)
            {
                return this->rooms[row][col];
            }
        }
    }

    // Not found
    return nullptr;
}


/*                                                                                      -
 * Function:		Game::game_over_screen()
 * Description:		Handles logic / user-input at the end of the game, such that, if
 *			    the user wants to play again, their choice of if they want
 *			    to do that with new dimensions or not is made clear, and whe-
 *			    her they're playing again or not is returned as a bool. This
 *			    is shown regardless of whether the player has won or lost.
 * Return Value:	Whether a new round will be played as a bool.
 * Pre-Conditions:	All fields instantiated. The user has either won or lost.
 * Post-Conditions:	If the player wants to play again, the game is ready for that new
 *			    round, and true is returned, if not, false is returned.
 */
bool Game::game_over_screen()
{
    bool result = false;

    /* Prompt */
    std::string message =
        "    .::::         .:        .::       .:: .::::::: \n  .:    .::      .: ::      .: .::   .::: .::      \n .::            .:  .::     .:: .:: . .:: .::      \n .::           .::   .::    .::  .::  .:: .:::::   \n .::   .::::  .:::::: .::   .::   .:  .:: .::      \n  .::    .:  .::       .::  .::       .:: .::      \n   .:::::   .::         .:: .::       .:: .::::::: \n\n     .::::    .::         .:: .:::::::: .::::::    \n   .::   .::   .::       .::  .::       .::   .::  \n .::      .::   .::     .::   .::       .::   .::  \n .::      .::    .::   .::    .::::::   .: .::     \n .::      .::     .:: .::     .::       .::  .::   \n   .::   .::       .::::      .::       .::   .::  \n     .::::          .::       .:::::::: .::    .:: \n\n+-------------------------------------------------+\n                                                   \n  Your journey has come to an end, and now you've  \n    arrived at a crossroads of sorts, wanderer!    \n\n                Make your decision:                \n\n           (1) Brave this Wumpus again!           \n           (2) Try another Wumpus lair!           \n           (q) Come back another day...           \n\0";

    this->general_alert->set_message(message.c_str());
    this->general_alert->make_visible();
    this->game_window->display();

    /* Get input */
    std::string choice;
    bool keep_going = true;

    while (keep_going)
    {
        choice = get_char_input();

        if (
            choice == "1" ||
            choice == "2" ||
            choice == "q" ||
            choice == "Q")
        {
            keep_going = false;
        }
    }

    this->general_alert->make_invisible();

    /* Handle input */
    if (choice == "1")
    {
        /* Replay cave with same positions of Events */

        // Clear Wumpus from wherever it is now
        Room * wumpus_room = find_wumpus_room();

        if (wumpus_room != nullptr)
        {
            wumpus_room->clear_event();
        }

        // Put Gold, Player, and Wumpus back in their initial positions
        this->p->move_to(exit_x, exit_y);

        if (this->init_gold_room != nullptr)
        {
            this->init_gold_room->set_event(new Gold());
        }

        if (this->init_wump_room != nullptr)
        {
            this->init_wump_room->set_event(new Wumpus());
        }

        // Reset other fields and values
        this->p->reset_arrows();
        this->p->set_has_killed_wumpus(false);
        this->p->set_has_gold(false);
        this->game_console->clear();
        enter_room();

        result = true;
    }
    else if (choice == "2")
    {
        /* Generate new cave with same dimensions */

        // Reset fields and values
        this->p->reset_arrows();
        this->p->set_has_killed_wumpus(false);
        this->p->set_has_gold(false);

        // Regenerate map
        generate_map(this->cave_width, this->cave_height);
        this->game_console->clear();
        enter_room();

        result = true;
    }
    else if (choice == "q" ||
             choice == "Q")
    {
        result = false;
    }

    update_ui();
    this->game_window->display();

    return result;
}


/*  Backup game over alert string:
 *
 *      "    .::::         .:        .::       .:: .::::::: \n"
 *    + "  .:    .::      .: ::      .: .::   .::: .::      \n"
 *    + " .::            .:  .::     .:: .:: . .:: .::      \n"
 *    + " .::           .::   .::    .::  .::  .:: .:::::   \n"
 *    + " .::   .::::  .:::::: .::   .::   .:  .:: .::      \n"
 *    + "  .::    .:  .::       .::  .::       .:: .::      \n"
 *    + "   .:::::   .::         .:: .::       .:: .::::::: \n"
 *    + "\n"
 *    + "     .::::    .::         .:: .:::::::: .::::::    \n"
 *    + "   .::   .::   .::       .::  .::       .::   .::  \n"
 *    + " .::      .::   .::     .::   .::       .::   .::  \n"
 *    + " .::      .::    .::   .::    .::::::   .: .::     \n"
 *    + " .::      .::     .:: .::     .::       .::  .::   \n"
 *    + "   .::   .::       .::::      .::       .::   .::  \n"
 *    + "     .::::          .::       .:::::::: .::    .:: \n"
 *    + "\n"
 *    + "+-------------------------------------------------+\n"
 *    + "                                                   \n"
 *    + "  Your journey has come to an end, and now you've  \n"
 *    + "    arrived at a crossroads of sorts, wanderer!    \n"
 *    + "\n"
 *    + "                Make your decision:                \n"
 *    + "\n"
 *    + "           (1) Brave this Wumpus again!            \n"
 *    + "           (2) Try another Wumpus lair!            \n"
 *    + "           (q) Come back another day...            \n";
 */
