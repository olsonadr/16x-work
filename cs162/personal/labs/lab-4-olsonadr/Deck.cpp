#include "Deck.hpp"
#include <iostream>

Deck::Deck() : deck_cards(new Card[52])
{
    // std::cout << "Deck constructed" << std::endl;
    this->n_cards = 52;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 0; rank < 13; rank++)
        {
            this->deck_cards[(suit * 13) + rank] = Card(rank, suit);
            // std::cout << this->deck_cards[(suit * 13) + rank].get_full_name() << std::endl;
        }
    }

}

Deck::Deck(const Deck &old_deck) : deck_cards(new Card[52])
{
    // std::cout << "Deck copied" << std::endl;
    this->n_cards = old_deck.n_cards;
    for (int i = 0; i < this->n_cards; i++)
    {
        this->deck_cards[i] = old_deck.deck_cards[i];
    }
}

Deck::~Deck()
{
    // std::cout << "Deck destructed" << std::endl;
    delete[] this->deck_cards;
}

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
        // std::cout << this->deck_cards[i].get_full_name() << std::endl;
    }
}

// DECK MUST HAVE CARDS IN IT
Card Deck::draw()
{
    this->n_cards--;
    // std::cout << deck_cards[n_cards].get_full_name() << std::endl;
    return this->deck_cards[this->n_cards];
}

void Deck::reset()
{
    this->n_cards = 52;
    shuffle();
}