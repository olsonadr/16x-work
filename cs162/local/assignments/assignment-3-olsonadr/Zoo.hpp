/*
 *  Program:		Zoo.hpp - Zoo Class Header File
 *  Author:		Nick Olson
 *  Date:		02/04/19
 *  Description:	The header file of the Zoo class, lists all include
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
        // Fields
        Animal *** animal_arrs; /* Array of Animal arrays (Monkey, Otter, Sloth) */
        int * arr_lens;		/* Length of each Animal array */
        int * arr_nums;		/* Number of Animals in each array */
        int * revenues;
        int * expenses;
        int num_species;
        int day_num;
        int base_food_cost;
        int boom_rev;
        bool any_sick;
        int prev_food_quality;	/* Of the day before, 0-2 is cheap, regular, premium. */
        int curr_food_quality;	/* Selected for current day, same possible values */
        int funds;
	std::mt19937 rng;
	std::uniform_int_distribution<int> name_gen;
	std::uniform_int_distribution<int> food_gen;
	std::uniform_int_distribution<int> species_gen;
	std::uniform_int_distribution<int> low_special_gen;
	std::uniform_int_distribution<int> reg_special_gen;
	std::uniform_int_distribution<int> sup_special_gen;



        // Functions
        void day_setup();
        void add_animal(Animal * new_animal);
        void remove_animal(int species_index, int animal_index);
        bool end_day(bool paying_for_meds = true);
        void update_rev_exp(bool paying_for_meds = true);
        void update_base_food();
        void grow_array(int species_index);
        void special_event();

        // Input + Output + Alert + Game Over Functions
        std::string input(std::string prompt = "");
        bool get_bool_input(std::string prompt = "");
        template <typename Head>
        void output(const Head & first);
        template <typename Head, typename... Tail>
        void output(const Head & first, const Tail & ... args);
        void alert(std::string message = "");
        void game_over_screen();
        void display();
        void buy_animal();
        void opening_screen();

    public:
        // Constructor + Destructor
        Zoo();
        ~Zoo();

        // General Functions
        void game_setup();
        bool day();
};

#endif
