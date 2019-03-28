/*
 *  Program:		Animal.cpp - Animal Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/04/19
 *  Description:	The implementation of the Animal class described in
 *                      Animal.hpp, objects of which represent...
 */


#include "Animal.hpp"


/*                                                                                      -
 *  Constructor:	Animal::Animal(...)
 *  Description:	Parameterized constructor for Animal class, no default values as
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
    update_age_group();
}


/*                                                                                      -
 *  Constructor:	Animal::Animal(...)
 *  Description:	Copy constructor for Animal class. Initializes all fields to vals
 *			    of the passed old_animal, checks whether Animal is baby, etc.
 *  Pre-conditions:     No fields have been instantiated.
 *  Post-conditions:    All fields have been instantiated.
 */
Animal::Animal(const Animal & old_animal)
    : name(old_animal.name), species(old_animal.species), age(old_animal.age),
      cost(old_animal.cost), num_babies(old_animal.num_babies),
      food_cost_mult(old_animal.food_cost_mult),
      revenue_mult(old_animal.revenue_mult)
{
    this->is_sick = old_animal.is_sick;
    update_age_group();
}


/*                                                                                      -
 *  Constructor:	void Animal::operator=(...)
 *  Description:	Overriden assignment operator for Animal class. Initializes all
 *			    fields to vals of the passed old_animal, checks whether the
 *			    Animal is baby, etc.
 *  Pre-conditions:     No fields have been instantiated.
 *  Post-conditions:    All fields have been instantiated.
 */
void Animal::operator=(const Animal & old_animal)
{
    this->name = old_animal.name;
    this->species = old_animal.species;
    this->age = old_animal.age;
    this->cost = old_animal.num_babies;
    this->food_cost_mult = old_animal.food_cost_mult;
    this->revenue_mult = old_animal.revenue_mult;
    this->is_sick = old_animal.is_sick;
    update_age_group();
}


/*                                                                                      -
 *  Function:		Animal::update_age_group()
 *  Description:	Updates the Animal's age_group field with its accurate age-group
 *			    where Baby represents under 30 days of age, Child represents
 *			    under 3 years of age, and adult is over 3 years.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    The age_group field is accurate to the current age.
 */
void Animal::update_age_group()
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


/*
 * Function:		Animal::day_passes()
 * Description:		Field mutations when a day passes, for all Animals, adds one day
 *			    to their age and updates age_group.
 * Pre-Conditions:	All fields instantiated.
 * Post-Conditions:	Fields are accurate to one day having passed.
 */
void Animal::day_passes()
{
    this->age++;
    update_age_group();
}


/*
 * Function:		Animal::get_revenue()
 * Description:		Gets how much revenue this Animal produces in a day based on its
 *			    revenue multiplier and whether or not it is a baby. This does
 *			    not handle the Monkey bonus from attendance booms.
 * Return Value:	The amount of revenue it generates in a day.
 * Pre-Conditions:	All fields instantiated, age_group is accurate to current age.
 * Post-Conditions:	Revenue has been returned.
 */
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
