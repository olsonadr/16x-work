#ifndef DECK_HPP
#define DECK_HPP

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