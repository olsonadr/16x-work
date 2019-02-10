/*
 *  Program:		Deck.cpp - Deck Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	The implementation of the Deck class described in
 *                      Deck.hpp, objects of which represent the deck
 *                      of Cards that will be played in the game.
 */

#include "Deck.hpp"

/*                                                                     -
 *  Constructor:   		Deck::Deck
 *  Description:		Default constructor for the Deck class, takes
 *                          nothing and instantiates all fields with
 *                          the deck in unshuffled order.
 *  Post-conditions:    Fields intitialized, deck unshuffled.
 */
Deck::Deck() : deck_cards(new Card[52])
{
    this->n_cards = 52;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 0; rank < 13; rank++)
        {
            this->deck_cards[(suit * 13) + rank] = Card(rank, suit);
        }
    }
}

/*                                                                     -
 *  Constructor:   		Deck::Deck
 *  Description:		Copy constructor for the Deck class, takes an old
 *                          Deck object, copies its cards and n_cards.
 *  Parameters:			const Deck &old_deck:
 *							The Deck to be copied.
 *  Post-conditions:    The fields have been instantiated with the values
 *                          of the passed Deck.
 */
Deck::Deck(const Deck &old_deck) : deck_cards(new Card[52])
{
    this->n_cards = old_deck.n_cards;
    for (int i = 0; i < this->n_cards; i++)
    {
        this->deck_cards[i] = old_deck.deck_cards[i];
    }
}

/*                                                                     -
 *  Destructor:   		Deck::~Deck
 *  Description:		Destructor for the Deck class, frees the memory
 *                          reserved for the Deck's cards.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    All memory has been free'd.
 */
Deck::~Deck()
{
    delete[] this->deck_cards;
}

/*                                                                     -
 *  Function:   		Deck::shuffle
 *  Description:		Randomizes the order of the cards in the Deck.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    The Deck is 'shuffled' into a random order.
 */
void Deck::shuffle()
{
    std::mt19937 rng(time(NULL));
    for (int i = 0; i < this->n_cards; i++)
    {
        std::uniform_int_distribution<int> gen(i, this->n_cards - 1);
        int rand_i = gen(rng);

        Card temp = this->deck_cards[i];
        this->deck_cards[i] = this->deck_cards[rand_i];
        this->deck_cards[rand_i] = temp;
    }
}

/*                                                                     -
 *  Function:   		Deck::draw
 *  Description:		'Draws' a card from the Deck by decrementing the
 *                          value of n_cards and returning the card that
 *                          is no longer 'in' the Deck. 
 *  Returns:            The Card that is 'drawn.'
 *  Pre-conditions:     All fields have been instantiated, n_cards > 0.
 *  Post-conditions:    n_cards has been decremented by one.
 */
Card Deck::draw()
{
    this->n_cards--;
    return this->deck_cards[this->n_cards];
}

/*                                                                     -
 *  Function:   		Deck::reset
 *  Description:		Resets the Deck back to its pre-game state by
 *                          setting n_cards back to 52, such that all
 *                          Cards are considered again, and shuffling
 *                          the Deck using shuffle().
 *  Pre-conditions:     All fields have been instantiated, game has been
 *                          played out as fully as the user wants.
 *  Post-conditions:    The Deck is reshuffled and ready for a new game.
 */
void Deck::reset()
{
    this->n_cards = 52;
    shuffle();
}