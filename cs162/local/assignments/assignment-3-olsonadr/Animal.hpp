/*
 *  Program:		    Animal.hpp - Animal Class Header File
 *  Author:		      Nick Olson
 *  Date:		        02/04/19
 *  Description:	  The header file of the Animal class, lists all include
 *                      statements and function prototypes for Animal class.
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal
{
protected:
  std::string name;
  std::string species;
  int age;
  int cost;
  int num_babies;
  int food_cost_mult;
  int revenue_mult;
  bool is_sick;
  std::string age_group;
  void update_baby_status();

public:
  // Constructors + Overloaded Constructor
  Animal(std::string name, std::string species,
         int age, int cost, int num_babies,
         int food_cost_mult, float revenue_mult);

  Animal(const Animal & old_animal);

  void operator=(const Animal & old_animal);

  // Accessors
  std::string get_name() { return this->name; }
  std::string get_species() { return this->species; }
  int get_age() { return this->age; }
  int get_cost() { return this->cost; }
  int get_num_babies() { return this->num_babies; }
  int get_food_cost_mult() { return this->food_cost_mult; }
  bool get_is_sick() { return this->is_sick; }
  std::string get_age_group() { return this->age_group; }
  void print_all();

  // Misc
  void day_passes();
  int get_revenue();
};

#endif