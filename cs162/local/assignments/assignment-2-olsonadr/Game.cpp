/*
 *  Program:		Game.cpp - Game Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	The implementation of the Game class described in
 *                      Game.hpp, used for running a game of Go Fish!
 */

#include "Game.hpp"
#include "help.hpp"

/*
 *  Constructor:		Game::Game
 *  Description:		Primary constructor for Game, taking desired
 *                          hand size as parameter, instantiates. Sets
 *                          user to human player and cpu to AI player.
 *  Parameters:			int hand_size:
 *							The desired starting hand size.
 *  Post-conditions:    All fields intitialized, user is human, cpu not.
 */
Game::Game(int hand_size) : cards(), user(false), cpu(true)
{
    // std::cout << "Game constructed" << std::endl;
    this->hand_size = hand_size;
    // this->players[0] = Player(false);
    // this->players[1] = Player(false); //Player(true);
    // std::cout << "Two players gone?" << std::endl;
}

/*
 *  Destructor:			Game::~Game
 *  Description:		Destructor that delete[]'s the players array.
 *  Pre-conditions:     players has not been freed.
 *  Post-conditions:    All dynamic memory in game has been freed.
 */
Game::~Game()
{
    // std::cout << "Game destructed" << std::endl;
    // delete[] this->players;
}

/*
 *  Function:			Game::setup
 *  Description:		Calls function to shuffle the deck and draw
 *                          (hand_size) cards into each player's hand.
 *  Pre-conditions:     Game is first starting or is being reset, this
 *                          is the first action taken in the game.
 *  Post-conditions:    Game is ready to be played, each player has the
 *                          starting number of cards, deck is shuffled.
 */
void Game::setup()
{
    this->cards.shuffle();
    // Card drawn = this->cards.draw();
    // std::cout << "Top Card = " << drawn.get_full_name() << std::endl;
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < this->hand_size; j++)
        {
            this->user.add_card(this->cards.draw());
            this->cpu.add_card(this->cards.draw());
        }
    }
}

/*
 *  Function:			Game::player_turn
 *  Description:		Represents the player turn and all displayed
 *                          information and logic. Displays the table,
 *                          asks for user input, checks request, and
 *                          handles what should happen next (draw, re-
 *                          peat of turn, end of turn, etc).
 *  Returns:            0 as int if execution was sucessful, 1 if the
 *                          super secret exit move was invoked.
 *  Pre-conditions:     setup() has been called and all fields have
 *                          been instantiated already. user is a human.
 *  Post-conditions:    Player (in user) has taken the extent of their
 *                          turn, however many rounds of input that
 *                          necessitates.
 */
int Game::player_turn()
{
    update_all_books();
    const std::string long_ranks[] = {
        "Aces", "Twos", "Threes", "Fours", "Fives",
        "Sixes", "Sevens", "Eights", "Nines", "Tens",
        "Jacks", "Queens", "Kings"};

    Player *p = &this->user;  //&this->players[0];
    Player *cpu = &this->cpu; //&this->players[1];

    std::system("CLS");
    std::system("clear");

    display_table();

    if ((*p).get_hand_size() <= 0)
    { /* Player's hand is empty */
        if (this->cards.get_n_cards() >= 1)
        {
            std::cout << "You must draw a card! Press enter..." << std::endl;
            std::getchar();
            (*p).add_card(this->cards.draw());
            return player_turn();
        }
        else
        {
            std::cout << "No more cards to draw! Press enter..." << std::endl;
            std::getchar();
            return 0;
        }
    }
    else
    { /* Player's hand is not empty */
        int requested_rank = get_valid_request();

        if (requested_rank == 13)
        { /* The user has invoked the super secret exit move */
            return 1;
        }

        if ((*cpu).is_held(requested_rank))
        { /* CPU has the requested card */
            int count_stolen = 0;

            do
            {
                (*p).add_card((*cpu).steal(requested_rank));
                count_stolen++;
            } while ((*cpu).is_held(requested_rank));

            std::cout << "The CPU gives you "
                      << count_stolen
                      << " "
                      << long_ranks[requested_rank]
                      << "!"
                      << std::endl
                      << "So you get to play again! Press enter..."
                      << std::endl;

            std::getchar();

            return player_turn();
        }
        else
        { /* CPU did not have the requested card */
            Card drawn_card = this->cards.draw();
            (*p).add_card(drawn_card);

            std::cout << "Go Fish! You draw the "
                      << drawn_card.get_full_name()
                      << "!"
                      << std::endl;

            if (drawn_card.get_rank() == requested_rank)
            {
                std::cout << "So you can play again! Press enter..."
                          << std::endl;

                std::getchar();

                return player_turn();
            }
            else
            { /* Drew card other than one requested */
                std::cout << "So your turn ends. Press enter..."
                          << std::endl;

                std::getchar();
                return 0;
            }
        }
    }
}

/*
 *  Function:			Game::cpu_turn
 *  Description:		Represents a turn by the CPU. Displays the cur-
 *                          rent table status, generates a random valid
 *                          request, then follows same logic as player's
 *                          turn, but only displaying pertinent information.
 *  Pre-conditions:     Setup has been called, fields instantiated, etc.
 *  Post-conditions:    CPU has played turn, however many moves that takes.
 */
void Game::cpu_turn()
{
    update_all_books();
    const std::string long_ranks[] = {
        "Aces", "Twos", "Threes", "Fours", "Fives",
        "Sixes", "Sevens", "Eights", "Nines", "Tens",
        "Jacks", "Queens", "Kings"};

    Player *p = &this->user;  //&this->players[0];
    Player *cpu = &this->cpu; //&this->players[1];

    std::system("CLS");
    std::system("clear");

    display_table();

    if ((*cpu).get_hand_size() <= 0)
    { /* cpu's hand is empty */
        if (this->cards.get_n_cards() >= 1)
        {
            std::cout << "CPU must draw a card! Press enter..." << std::endl;
            std::getchar();
            (*cpu).add_card(this->cards.draw());
            return cpu_turn();
        }
        else
        {
            std::cout << "CPU passes its turn! Press enter..." << std::endl;
            std::getchar();
            return;
        }
    }
    else
    { /* cpu's hand is not empty */
        int requested_rank = (*cpu).random_card();

        if ((*p).is_held(requested_rank))
        { /* player has the requested card */
            int count_stolen = 0;

            do
            {
                (*cpu).add_card((*p).steal(requested_rank));
                count_stolen++;
            } while ((*p).is_held(requested_rank));

            std::cout << "The CPU takes all your "
                      << long_ranks[requested_rank]
                      << "!"
                      << std::endl
                      << "So it gets to play again. Press enter..."
                      << std::endl;

            std::getchar();

            return cpu_turn();
        }
        else
        { /* player did not have the requested card */
            Card drawn_card = this->cards.draw();
            (*cpu).add_card(drawn_card);

            std::cout << "The CPU asks for all your "
                      << long_ranks[requested_rank]
                      << ""
                      << std::endl
                      << "Go Fish! The CPU draws a card!"
                      << std::endl;

            if (drawn_card.get_rank() == requested_rank)
            {
                std::cout << "And it can play again! Press enter..."
                          << std::endl;

                std::getchar();

                return cpu_turn();
            }
            else
            { /* Drew card other than one requested */
                std::cout << "And its turn ends. Press enter..."
                          << std::endl;

                std::getchar();
                return;
            }
        }
    }
}

/*
 *  Function:			Game::display_table
 *  Description:		Prints out the current state of all the elements
 *                          on the simulated table (cpu's hand [hidden],
 *                          num cards in deck, each player's books, your
 *                          hand's contents, etc) to cout.
 *  Pre-conditions:     All fields instantiated.
 *  Post-conditions:    The table has been printed to cout.
 */
void Game::display_table()
{
    std::cout << "#=~"
              << std::endl
              << "CPU's:"
              << std::endl
              << "  ";
    this->cpu.display_hand(); //players[1].display_hand();
    std::cout << "  ";
    this->cpu.display_books(); //players[1].display_books();
    std::cout << std::endl
              << std::endl
              << "                                 [ "
              << std::setfill('0') << std::setw(2)
              << this->cards.get_n_cards()
              << " ]"
              << std::endl
              << std::endl;
    std::cout << "Your:"
              << std::endl
              << "  ";
    this->user.display_books(); //players[0].display_books();
    std::cout << "  ";
    this->user.display_hand(); //players[0].display_hand();
    std::cout << "#=~"
              << std::endl;
}

/*
 *  Function:			Game::get_valid_request
 *  Description:		Prompts the user for input and takes user input from
 *                          cin as a string, accepting only valid inputs such
 *                          that the input is the short or long rank of a card
 *                          in their Hand.
 *  Parameters:			int player_num:
 *							The player whose hand to check input against.
 *  Returns:			The rank of the user's choice as a int value.
 *  Pre-conditions:     player_num points to an initialized player, player's
 *                          hand is NOT EMPTY (please).
 */
int Game::get_valid_request(
    int player_num)
{
    int input = -1;
    int num_options = 28;
    std::string options[] = {
        "A", "2", "3", "4", "5",
        "6", "7", "8", "9", "10",
        "J", "Q", "K", "E",
        "Ace", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten",
        "Jack", "Queen", "King", "Exit"};

    Player *p = &this->user; //&this->players[player_num];
    bool keep_going = true;

    while (keep_going)
    {
    input = HelperLib::getIndexInputOfStringList(
        "Ask for a rank (\'A\'/\'Ace\', \'2\'/\'Two\', etc.)",
        options, num_options, false);

    input = input % 14;

        if ((*p).is_held(input) || input == 13)
        {
            keep_going = false;
        }
        else
        {
            std::cout << "You don't have this card! Try again."
                      << std::endl;
        }
    }

    return input;
}

/*
 *  Function:			Game::check_game_over
 *  Description:		Checks if the game is over by checking total num
 *                          of books claimed, congratulates winner if game
 *                          should be over. If game is being forced to end,
 *                          congratulates player with most books.
 *  Parameters:			bool forced_end:
 *							Whether the game is being forced to end early,
                            defaults to true in .hpp file, such that this
                            is only ever intentionally called.
 *  Returns:			Whether the game should be over.
 *  Pre-conditions:     All values instantiated, game has started.
 *  Post-conditions:    If all books have been placed down or forced_end is
 *                          true, winner has been acknowledged and true has
 *                          been returned, false otherwise.
 */
bool Game::check_game_over(bool forced_end)
{
    int total_books = 0;
    Player *ptrs[2] = {&user, &cpu};
    for (int i = 0; i < 2; i++)
    {
        total_books += (*ptrs[i]).get_n_books(); //this->players[i].get_n_books();
    }
    if (total_books >= 13 || forced_end)
    { // Game is being forced to end or all books have been claimed.
        std::cout << "Congratulations, ";
        if (this->user.get_n_books() > this->cpu.get_n_books())
        {
            std::cout << "player! ";
        }
        else if (this->cpu.get_n_books() > this->user.get_n_books())
        {
            std::cout << "CPU! ";
        }
        else
        {
            std::cout << "both of you! You found a way to tie! ";
        }
        std::cout << "You've won!"
                  << std::endl
                  << "#=~"
                  << std::endl;
        return true;
    }

    return false;
}

/*
 *  Function:			Game::update_all_books
 *  Description:		Calls the function to update the books for each
 *                          player if they need to be.
 *  Pre-conditions:     All fields instantiated.
 *  Post-conditions:    Books for both user and cpu have been updated.
 */
void Game::update_all_books()
{
    this->user.update_books();
    this->cpu.update_books();
    // for (int i = 0; i < 2; i++)
    // {
    //     this->players[i].update_books();
    // }
}

/*
 *  Function:			Game::reset
 *  Description:		Calls each player's and the deck's reset() function
 *                          such that the game is ready for a new round of
 *                          gameplay (deck shuffled, arrays 'emptied', etc.) 
 *  Pre-conditions:     Game was played and should be reset for a new round.
 *  Post-conditions:    Game is reset and ready for a new round.
 */
void Game::reset()
{
    this->user.reset();
    this->cpu.reset();
    /*
    for (int i = 0; i < 2; i++)
    {
        this->players[i].reset();
    }
    */
    this->cards.reset();
    setup();
}