/*
 *  Program:		    Zoo.hpp - Zoo Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/04/19
 *  Description:	  The header file of the Zoo class, lists all include
 *                      statements and function prototypes for Zoo class.
 */

#ifndef ZOO_HPP
#define ZOO_HPP

#include <string>
#include <random>
#include <iomanip>
#include <iostream>
#include "Monkey.hpp"
#include "Sloth.hpp"
#include "Otter.hpp"

class Zoo
{
  private:
    Animal *** animal_arrs; /* Array of Animal arrays (Monkey, Otter, Sloth) */
    int * arr_lens; /* Length of each Animal array */
    int * arr_nums; /* Number of Animals in each array */
    int * revenues;
    int * expenses;
    int num_species;
    int day_num;
    int base_food_cost;
    int funds;
    void game_setup();
    void day_setup();
    void add_animal(Animal * new_animal);
    void remove_animal(int species_index, int animal_index);
    bool end_day(bool paying_for_meds = true);
    void update_rev_exp(bool paying_for_meds = true);
    void update_base_food();
    void grow_array(int species_index);
    // void display();

  public:
    Zoo();
    ~Zoo();
    void display();

    // Accessors

    // Mutators

    // General
    bool day(  );
};

#endif