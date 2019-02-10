/*
 *  Program:		Card.cpp - Card Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	The implementation of the Card class described in
 *                      Card.hpp, objects of which represent individual
 *                      cards that will be played in the game.
 */

#include "Card.hpp"

/*                                                                     -
 *  Constructor:   		Card::Card
 *  Description:		Default constructor for the Card class, which
 *                          instantiates the Card as an Ace of Clubs
 *                          but with an empty name.
 *  Post-conditions:    All fields intitialized as a blank card.
 */
Card::Card()
{
    this->rank = 0;
    this->suit = 0;
    this->name = "";
}

/*
 *  Constructor:		Card::Card
 *  Description:		Primary constructor for Card instantiates all
 *                          fields to passed values and determining the
 *                          std::string representation.
 *  Parameters:			int rank:
 *							The desired rank of the card, 0-12 for A-K.
 *                      int suit:
 *                          The desired suit of the card, 0-3 for "Clubs,"
 *                          "Diamonds," "Hearts," and "Spades."
 *  Post-conditions:    All fields intitialized with desired rank and suit.
 */
Card::Card(int rank, int suit)
{
    std::string short_ranks[13] = {
        ".A", ".2", ".3", ".4", ".5",
        ".6", ".7", ".8", ".9", "10",
        ".J", ".Q", ".K"};
    std::string short_suits[4] = {
        "C", "D", "H", "S"};
    this->rank = rank;
    this->suit = suit;
    this->name = short_ranks[this->rank] + short_suits[this->suit];
}

/*
 *  Constructor:		Card::Card
 *  Description:		Copy constructor for Card instantiates all
 *                          fields to the values of the passed card and
 *                          determining the std::string representation.
 *  Parameters:			Card &old_card:
 *							The card to be copied.
 *  Post-conditions:    All fields intitialized with fields of passed card.
 */
Card::Card(const Card &old_card)
{
    this->rank = old_card.rank;
    this->suit = old_card.suit;
    this->name = old_card.name;
}

/*
 *  Function:		    Card::operator=
 *  Description:		Overloaded = operator for the Card class, such that
 *                          using = copies the fields from the right side to
 *                          the left consistently.
 *  Parameters:			Card &old_card:
 *							The card whose fields will be stored.
 *  Post-conditions:    All fields reset to value of passed card.
 */
void Card::operator=(const Card &old_card)
{
    this->rank = old_card.rank;
    this->suit = old_card.suit;
    this->name = old_card.name;
}

/*                                                                     -
 *  Function:   		Card::get_long_rank()
 *  Description:		Returns the full word std::string representation of
 *                          the card ("Ace" or "Two").
 *  Returns:            The std::string representation of the rank (word).
 *  Pre-conditions:     All fields have been instantiated.
 */
std::string Card::get_long_rank()
{
    std::string long_ranks[13] = {
        "Ace", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten",
        "Jack", "Queen", "King"};
    return long_ranks[this->rank];
}

/*                                                                     -
 *  Function:   		Card::get_full_name()
 *  Description:		Returns the full name representation of the card as
 *                          an std::string ("Ace of Spades" or "Seven of
 *                          Diamonds" for example).
 *  Returns:            The std::string representation of the card with rank
 *                          and suit as full words.
 *  Pre-conditions:     All fields have been instantiated.
 */
std::string Card::get_full_name()
{
    std::string long_ranks[13] = {
        "Ace", "Two", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten",
        "Jack", "Queen", "King"};
    std::string long_suits[4] = {
        "Clubs", "Diamonds", "Hearts", "Spades"};
    return long_ranks[this->rank] + " of " + long_suits[this->suit];
}