/*
 *  Program:		    Monkey.hpp - Monkey Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/04/19
 *  Description:	  The header file of the Monkey class, lists all include
 *                      statements and function prototypes for Monkey class.
 */

#ifndef MONKEY_HPP
#define MONKEY_HPP

#include "Animal.hpp"
#include <string>
#include <random>

class Monkey : public Animal
{
public:
  Monkey(bool is_store_bought = false, std::string name = "George")
      : Animal(name, "Monkey", (is_store_bought) ? (3 * 365) : (0), 15000, 1, 4, .1) {}
  
  // Overriden Accessor
  int get_revenue(bool is_boom);
};

#endif