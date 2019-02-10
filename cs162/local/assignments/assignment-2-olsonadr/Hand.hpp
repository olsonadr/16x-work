/*
 *  Program:		    Hand.hpp - Hand Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/03/2019
 *  Description:	  The header file of the Hand class, lists all include
 *                      statements and function prototypes for Hand class.
 */

#ifndef HAND_HPP
#define HAND_HPP

#include <iostream>
#include <random>
#include "Card.hpp"

class Hand
{
  private:
    Card *hand_cards;
    int n_cards;
    void swap(int first, int second);

  public:
    Hand();
    Hand(const Hand &old_hand);
    ~Hand();
    void operator=(const Hand &old_hand);
    int get_n_cards() { return this->n_cards; }
    int get_rank_of(int index) { return this->hand_cards[index].get_rank(); }
    void display(bool is_hidden);
    void add(Card new_card);
    Card steal(int rank);
    bool is_held(int rank);
    int random();
    int check_books();
    void reset();
};

#endif