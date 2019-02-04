#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <iostream>

class Card
{
private:
  int rank;
  int suit;
  std::string name;

  // Constant lists for string representations
  std::string short_ranks[13] = {
      ".A", ".2", ".3", ".4", ".5",
      ".6", ".7", ".8", ".9", "10",
      ".J", ".Q", ".K"};
  std::string short_suits[4] = {
      "C", "D", "H", "S"};
  std::string long_ranks[13] = {
      "Ace", "Two", "Three", "Four", "Five",
      "Six", "Seven", "Eight", "Nine", "Ten",
      "Jack", "Queen", "King"};
  std::string long_suits[4] = {
      "Clubs", "Diamonds", "Hearts", "Spades"};

public:
  Card();
  Card(int m_rank, int m_suit);
  Card(const Card &old_card);
  int get_rank() { return this->rank; }
  int get_suit() { return this->suit; }
  std::string get_name() { return this->name; }
  bool is_valid() { return (this->name.length() != 0); }
  std::string get_long_rank();
  std::string get_full_name();
};

#endif