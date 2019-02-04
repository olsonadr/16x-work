#include "Hand.hpp"
#include "Deck.hpp"
#include "Card.hpp"

int main()
{
    Hand hand;
    Deck deck;
    deck.shuffle();
    for (int i = 0; i < 7; i++)
    {
	hand.add(deck.draw());
    }
    hand.display(false);
}
