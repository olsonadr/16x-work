/*
 *  Program:		Player.cpp - Player Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	The implementation of the Player class described in
 *                      Player.hpp, objects of which represent Players
 *                      in the game which each have a Hand of Cards.
 */

#include "Player.hpp"

/*                                                                     -
 *  Function:   		Player::
 *  Description:		d
 *  Parameters:			v:
 *							d
 *  Returns:            r
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    p
 */

const char *ranks[] = {
    "A", "2", "3", "4", "5",
    "6", "7", "8", "9", "10",
    "J", "Q", "K"};

/*                                                                     -
 *  Constructor:   		Player::Player
 *  Description:		Primary and default constructor for Player class.
 *                          Takes whether the player is a CPU (defaults 
 *                          to false) and instantiates all fields, reser-
 *                          ving memory as needed.
 *  Parameters:			bool is_cpu:
 *							Whether Player is a CPU (defaults to false).
 *  Post-conditions:    All fields have been instantiated.
 */
Player::Player(bool is_cpu) : hand(), books(new int[13])
{
    // std::cout << "Player constructed" << std::endl;
    this->n_books = 0;
    this->is_cpu = is_cpu;
}

/*                                                                     -
 *  Constructor:   		Player::Player
 *  Description:		Copy constructor for Player class. Takes Player
 *                          object and instantiates all fields to values
 *                          of passed Player object.
 *  Parameters:			const Player &old_player:
 *							The Player to be copied.
 *  Post-conditions:    All fields have been instantiated.
 */
Player::Player(const Player &old_player)
{
    this->hand = old_player.hand;
    this->books = new int[13];
    this->n_books = old_player.n_books;
    this->is_cpu = old_player.is_cpu;
    for (int i = 0; i < this->n_books; i++)
    {
        this->books[i] = old_player.books[i];
    }
}

/*                                                                     -
 *  Destructor:   		Player::~Player
 *  Description:		Destructor for Player class, frees all memory.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    All memory has been free'd.
 */
Player::~Player()
{
    if (this->books != nullptr)
    {
        delete[] this->books;
    }
}

/*                                                                     -
 *  Function:   		Player::display_books
 *  Description:		Prints the ranks of each of the books collected
 *                          by this Player on a single line, to cout.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    Player's books have been printed to cout.
 */
void Player::display_books()
{
    std::cout << "Books: ";
    for (int i = 0; i < this->n_books; i++)
    {
        if (this->books[i] == 9)
        {
            std::cout << "[ 10 ] ";
        }
        else
        {
            std::cout << "[ "
                      << ranks[this->books[i]]
                      << " ] ";
        }
    }
    std::cout << std::endl;
}

/*                                                                     -
 *  Function:   		Player::update_books
 *  Description:		Adds all held books to the Player's books array
 *                          using Hand::check_books() until no books are
 *                          found, incrementing n_books as needed.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    Player's books array accurately represents all
 *                          books they have collected thus far.
 */
void Player::update_books()
{
    int book_rank = this->hand.check_books();

    while (book_rank != -1)
    {
        this->books[this->n_books] = book_rank;
        this->n_books++;

        book_rank = this->hand.check_books();
    }
}

/*                                                                     -
 *  Function:   		Player::reset
 *  Description:		Resets the Player object to be ready for a new
 *                          round of the game, setting n_books to 0 and
 *                          calling reset() on Player's Hand.
 *  Pre-conditions:     All fields have been instantiated, game is over.
 *  Post-conditions:    Player and Player's Hand are ready for new round.
 */
void Player::reset()
{
    this->n_books = 0;
    this->hand.reset();
}