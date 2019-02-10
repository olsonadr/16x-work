/*
 *  Program:		    Player.hpp - Player Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/03/2019
 *  Description:	  The header file of the Player class, lists all include
 *                      statements and function prototypes for Player class.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Hand.hpp"
#include <iostream>

class Player
{
  private:
    Hand hand;
    int *books;
    int n_books;
    bool is_cpu;

  public:
    // Constructor and Destructor
    Player(bool is_cpu = false);
    Player(const Player &old_player);
    ~Player();
    // Accessors
    int get_n_books() { return this->n_books; }
    // Short functions
    void add_card(Card card) { this->hand.add(card); }
    void display_hand() { this->hand.display(is_cpu); }
    int get_hand_size() { return this->hand.get_n_cards(); }
    int get_rank_of_card(int index) { return this->hand.get_rank_of(index); }
    Card steal(int rank) { return this->hand.steal(rank); }
    bool is_held(int rank) { return this->hand.is_held(rank); }
    int random_card() { return this->hand.random(); }
    // Longer functions
    void display_books();
    void update_books();
    void reset();
};

#endif