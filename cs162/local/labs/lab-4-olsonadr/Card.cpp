#include "Card.hpp"

Card::Card()
{
    this->rank = 0;
    this->suit = 0;
    this->name = "";
}

Card::Card(int rank, int suit)
{
    this->rank = rank;
    this->suit = suit;
    this->name = short_ranks[this->rank] + short_suits[this->suit];
}

Card::Card(const Card & old_card)
{
    this->rank = old_card.rank;
    this->suit = old_card.suit;
    this->name = short_ranks[this->rank] + short_suits[this->suit];
}

std::string Card::get_long_rank()
{
    return long_ranks[this->rank];
}

std::string Card::get_full_name()
{
    return long_ranks[this->rank] + " of " + long_suits[this->suit];
}

// bool Card::is_valid() { return (this->name.length() != 0); }