/*
 *  Program:		Card.hpp - Card Class Header File
 *  Author:		    Nick Olson
 *  Date:		    02/03/2019
 *  Description:	The header file of the Card class, lists all include
 *                      statements and function prototypes for Card class.
 */

#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>

class Card
{
private:
  int rank;
  int suit;
  std::string name;

public:
  Card();
  Card(int m_rank, int m_suit);
  Card(const Card &old_card);
  void operator=(const Card &old_card);
  int get_rank() { return this->rank; }
  int get_suit() { return this->suit; }
  std::string get_name() { return this->name; }
  bool is_valid() { return (this->name.length() != 0); }
  std::string get_long_rank();
  std::string get_full_name();
};

#endif