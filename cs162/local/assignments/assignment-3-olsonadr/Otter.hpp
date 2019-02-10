/*
 *  Program:		    Otter.hpp - Otter Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/04/19
 *  Description:	  The header file of the Otter class, lists all include
 *                      statements and function prototypes for Otter class.
 */

#ifndef OTTER_HPP
#define OTTER_HPP

#include "Animal.hpp"

class Otter : public Animal
{
public:
  Otter(bool is_store_bought = false, std::string name = "Phillipe")
      : Animal(name, "Otter", (is_store_bought) ? (3 * 365) : (0), 5000, 2, 2, .05) {}
};

#endif