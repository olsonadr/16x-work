/*
 *  Program:		    Deck.hpp - Deck Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/03/2019
 *  Description:	  The header file of the Deck class, lists all include
 *                      statements and function prototypes for Deck class.
 */

#ifndef DECK_HPP
#define DECK_HPP

#include <iostream>
#include <random>
#include "Card.hpp"

class Deck
{
  private:
    Card *deck_cards;
    int n_cards;

  public:
    Deck();
    Deck(const Deck &old_deck);
    ~Deck();
    int get_n_cards() { return this->n_cards; }
    void shuffle();
    Card draw();
    void reset();
};

#endif