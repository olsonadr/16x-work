/*
 *  Program:		    Game.hpp - Game Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/03/2019
 *  Description:	  The header file of the Game class, lists all include
 *                      statements and function prototypes for Game class.
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <iomanip>
#include "Deck.hpp"
#include "Player.hpp"

class Game
{
private:
  Deck cards;
  Player *players;
  Player user;
  Player cpu;
  int hand_size;

public:
  Game(int hand_size = 7);
  ~Game();
  void setup();
  int player_turn();
  void cpu_turn();
  void display_table();
  int get_valid_request(int player_num = 0);
  bool check_game_over(bool forced_end = false);
  void update_all_books();
  void reset();
};

#endif