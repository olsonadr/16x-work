/*
 *  Program:		Sloth.hpp - Sloth Class Header File
 *  Author:		Nick Olson
 *  Date:		02/04/19
 *  Description:	The header file of the Sloth class, lists all include
 *                      statements and function prototypes for Sloth class.
 */

#ifndef SLOTH_HPP
#define SLOTH_HPP

#include "Animal.hpp"

class Sloth : public Animal
{
    public:
        Sloth(bool is_store_bought = false, std::string name = "Jeremy")
            : Animal(name, "Sloth", (is_store_bought) ? (3 * 365) : (0), 2000, 3, 1, .05) {}
};

#endif
