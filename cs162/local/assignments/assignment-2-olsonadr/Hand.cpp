/*
 *  Program:		Hand.cpp - Hand Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	The implementation of the Hand class described in
 *                      Hand.hpp, objects of which represent the Cards
 *                      each player holds and can act based on.
 */

#include "Hand.hpp"

/*                                                                     -
 *  Function:   		Hand::
 *  Description:		d
 *  Parameters:			v:
 *							d
 *  Returns:            r
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    p
 */

/*                                                                     -
 *  Constructor:   		Hand::Hand
 *  Description:		Default constructor for Hand class, intantiates
 *                          fields such that it appears empty to program
 *                          but there are 40 default Cards ready to be
 *                          manipulated when Cards are added to the hand.
 *  Post-conditions:    All fields instantiated to an 'empty' Hand state.
 */
Hand::Hand()
{
    hand_cards = new Card[40];
    this->n_cards = 0;
}

/*                                                                     -
 *  Constructor:   		Hand::Hand
 *  Description:		Copy constructor for the Hand class, instantiates
 *                          all fields by copying the cards from a passed
 *                          Hand object.
 *  Parameters:			const Hand &old_hand:
 *							The Hand to be copied.
 *  Post-conditions:    All fields instantiated to the state of the passed
 *                          Hand object.
 */
Hand::Hand(const Hand &old_hand)
{
    this->n_cards = old_hand.n_cards;
    for (int i = 0; i < this->n_cards; i++)
    {
        this->hand_cards[i] = old_hand.hand_cards[i];
    }
}

/*                                                                     -
 *  Destructor:   		Hand::~Hand
 *  Description:		Frees all memory reserved for the Hand object.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    All memory (hand_cards) has been free'd.
 */
Hand::~Hand()
{
    delete[] this->hand_cards;
}

/*
 *  Function:		    Hand::operator=
 *  Description:		Overloaded = operator for the Hand class, such that
 *                          using = copies the fields from the right side to
 *                          the left consistently.
 *  Parameters:			Hand &old_hand:
 *							The Hand whose fields will be stored.
 *  Post-conditions:    All fields reset to value of passed Hand.
 */
void Hand::operator=(const Hand &old_hand)
{
    this->n_cards = old_hand.n_cards;
    for (int i = 0; i < this->n_cards; i++)
    {
        this->hand_cards[i] = old_hand.hand_cards[i];
    }
}

/*                                                                     -
 *  Function:   		Hand::diplay
 *  Description:		Displays the contents of the Hand to a single
 *                          line using two or three character strings
 *                          for each Card's rank and suit to cout. If
 *                          the hand should be hidden, prints out blank
 *                          Cards instead. ("[ RS ] or [ RRS ]" rep.)
 *  Parameters:			bool is_hidden:
 *							Whether the Cards should be hidden from the
                            player while printing.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    The Hand has been printed out to cout.
 */
void Hand::display(bool is_hidden)
{
    std::cout << "Hand:  ";
    if (this->n_cards > 0)
    {
        if (is_hidden)
        {
            for (int i = 0; i < this->n_cards; i++)
            {
                std::cout << "[     ] ";
            }
        }
        else
        {
            for (int i = 0; i < this->n_cards; i++)
            {
                if (this->hand_cards[i].get_rank() == 9)
                {
                    std::cout << "[ "
                              << this->hand_cards[i].get_name()
                              << " ] ";
                }
                else
                {
                    std::cout << "[ "
                              << this->hand_cards[i].get_name()
                              << " ] ";
                }
            }

            // Printed out indices when that was necessary:
            // std::cout << std::endl
            //           << "         ";

            // for (int i = 0; i < this->n_cards; i++)
            // {
            //     if (i < 10)
            //     {
            //         std::cout << " ";
            //     }
            //     std::cout << " ("
            //               << i
            //               << ")   ";
            // }
        }
    }
    else
    {
        std::cout << "<empty>";
    }
    std::cout << std::endl;
}

/*                                                                     -
 *  Function:   		Hand::add
 *  Description:		Adds the passed Card object to the Cards of the
 *                          Hand, incrementing n_cards.
 *  Parameters:			Card new_card:
 *							The Card to be added to the Hand.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    The Card has been added to the Hand, n_cards has
 *                          been incremented by one.
 */
void Hand::add(Card new_card)
{
    this->hand_cards[this->n_cards] = new_card;
    this->n_cards++;
}

/*                                                                     -
 *  Function:   		Hand::steal
 *  Description:		If a Card of the passed rank is held in this Hand,
 *                          returns the first instance of that Card object.
 *  Parameters:			int rank:
 *							The rank to be stolen.
 *  Returns:            The first instance of a Card of the passed rank in
 *                          the Hand, if it exists, else a defualt card.
 *  Pre-conditions:     n_cards >= 0.
 *  Post-conditions:    If a Card of that rank was held, n_cards has been
 *                          decremented, and the Card has been 'taken away.'
 */
Card Hand::steal(int rank)
{
    for (int i = 0; i < this->n_cards; i++)
    {
        if (this->hand_cards[i].get_rank() == rank)
        {
            this->n_cards--;
            swap(i, this->n_cards);
            return this->hand_cards[this->n_cards];
        }
    }
    return Card();
}

/*                                                                     -
 *  Function:   		Hand::is_held
 *  Description:		Checks this Hand for a Card of the given rank,
 *                          returns true if any are found.
 *  Parameters:			int rank:
 *							The rank to be searched for.
 *  Returns:            Whether the Card is held in the Hand as a bool.
 *  Pre-conditions:     n_cards is initialized.
 */
bool Hand::is_held(int rank)
{
    for (int i = 0; i < this->n_cards; i++)
    {
        if (this->hand_cards[i].get_rank() == rank)
        {
            return true;
        }
    }

    return false;
}

/*                                                                     -
 *  Function:   		Hand::random
 *  Description:		Returns the rank of a random card in the Hand;
 *                          used for CPU turns primarily.
 *  Returns:            The rank of a random card in the Hand as an int.
 *  Pre-conditions:     All fields have been instantiated.
 */
int Hand::random()
{
    std::mt19937 rng(time(NULL));
    std::uniform_int_distribution<int> gen(0, this->n_cards - 1);
    int rand_i = gen(rng);
    return this->hand_cards[rand_i].get_rank();
}

/*                                                                     -
 *  Function:   		Hand::check_books
 *  Description:		Checks the Hand for any books (sets of four), if
 *                          any are found, the first is removed from the
 *                          Hand by swapping each Card of that rank to
 *                          the end of the valid area of cards array, and
 *                          decrementing n_cards. If a book was found,
 *                          returns the rank of those cards. This only
 *                          handles the first book found, so subsequent
 *                          executions will be required.
 *  Returns:            The rank of the first book found, as an int, -1
 *                          if no book are found in the Hand.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    If a book was held, n_cards is decremented by 4.
 */
int Hand::check_books()
{
    int card_counts[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int book_rank = -1;

    for (int i = 0; i < this->n_cards; i++)
    {
        card_counts[this->hand_cards[i].get_rank()]++;
        if (card_counts[this->hand_cards[i].get_rank()] == 4)
        {
            book_rank = this->hand_cards[i].get_rank();
            for (int j = 0; j < this->n_cards; j++)
            {
                if (this->hand_cards[j].get_rank() == book_rank)
                {
                    this->n_cards--;
                    swap(j, this->n_cards);
                    j--;
                }
            }
        }
    }

    return book_rank;
}

/*                                                                     -
 *  Function:   		Hand::swap
 *  Description:		Private method that swaps the two cards in the
 *                          Hand at the passed two indices.
 *  Parameters:			int first:
 *							The index of the first Card to be swapped.
 *                      int second:
 *                          The index of the second Card to be swapped.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    The two cards have swapped positions in the Hand.
 */
void Hand::swap(int first, int second)
{
    Card temp = this->hand_cards[first];
    this->hand_cards[first] = this->hand_cards[second];
    this->hand_cards[second] = temp;
}

/*                                                                     -
 *  Function:   		Hand::reset
 *  Description:		Resets the Hand to its pre-game state for a new
 *                          round to be played, setting n_cards to 0.
 *  Pre-conditions:     All fields have been instantiated, game is over.
 *  Post-conditions:    Hand is ready for a new round to be played and
 *                          n_cards = 0.
 */
void Hand::reset()
{
    this->n_cards = 0;
}