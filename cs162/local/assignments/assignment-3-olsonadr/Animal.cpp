/*
 *  Program:		Animal.cpp - Animal Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/04/19
 *  Description:	The implementation of the Animal class described in
 *                      Animal.hpp, objects of which represent... 
 */

#include "Animal.hpp"
#include <iostream>

/*                                                                                      -
 *  Constructor:   		Animal::Animal
 *  Description:		Parameterized constructor for Animal class, no default values as
 *                          the Animal class should never be constructed. Initializes all
 *                          fields to passed values, checks whether Animal is baby, etc.
 *  Pre-conditions:     No fields have been instantiated.
 *  Post-conditions:    All fields have been instantiated.
 */
Animal::Animal(std::string name, std::string species,
               int age, int cost, int num_babies,
               int food_cost_mult, float revenue_mult)
    : name(name), species(species), age(age),
      cost(cost), num_babies(num_babies),
      food_cost_mult(food_cost_mult), revenue_mult(revenue_mult)
{
    this->is_sick = false;
    update_baby_status();
}

Animal::Animal(const Animal &old_animal)
    : name(old_animal.name), species(old_animal.species), age(old_animal.age),
      cost(old_animal.cost), num_babies(old_animal.num_babies),
      food_cost_mult(old_animal.food_cost_mult),
      revenue_mult(old_animal.revenue_mult)
{
    this->is_sick = old_animal.is_sick;
    update_baby_status();
}

void Animal::operator=(const Animal & old_animal)
{
    this->name = old_animal.name;
    this->species = old_animal.species;
    this->age = old_animal.age;
    this->cost = old_animal.num_babies;
    this->food_cost_mult = old_animal.food_cost_mult;
    this->revenue_mult = old_animal.revenue_mult;
    this->is_sick = old_animal.is_sick;
    update_baby_status();
}

/*                                                                                      -
 *  Function:   		Animal::update_baby_status()
 *  Description:		a
 *  Returns:            _ as a void
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    a
 */
void Animal::update_baby_status()
{
    if (this->age < 30)
    {
        this->age_group = "Baby";
    }
    else if (this->age < 3 * 365)
    {
        this->age_group = "Child";
    }
    else
    {
        this->age_group = "Adult";
    }
}

void Animal::day_passes()
{
    this->age++;
    update_baby_status();
}

// Pre-condition:   age_group is accurate
int Animal::get_revenue()
{
    if (this->age_group == "Baby")
    {
        return 2 * this->cost * this->revenue_mult;
    }
    else
    {
        return this->cost * this->revenue_mult;
    }
}

void Animal::print_all()
{
    std::cout << "Name:         "
              << this->name << std::endl
              << "Species:      "
              << this->species << std::endl
              << "Age:          "
              << this->age << std::endl
              << "Age Group:    "
              << this->age_group << std::endl
              << "Cost:         "
              << this->cost << std::endl
              << "Num Babies:   "
              << this->num_babies << std::endl
              << std::endl;
}