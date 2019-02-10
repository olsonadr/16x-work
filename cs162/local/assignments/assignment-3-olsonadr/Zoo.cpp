/*
 *  Program:		Zoo.cpp - Zoo Class Implementation File
 *  Author:		    Nick Olson
 *  Date:		    02/04/19
 *  Description:	The implementation of the Zoo class described in
 *                      Zoo.hpp, objects of which represent... 
 */

#include "Zoo.hpp"

Zoo::Zoo()
    : num_species(3), day_num(0), funds(100000), base_food_cost(50),
      arr_lens(new int[this->num_species]), arr_nums(new int[this->num_species]),
      animal_arrs(new Animal **[this->num_species]),
      revenues(new int[this->num_species]), expenses(new int[this->num_species])
{
    for (int species = 0; species < this->num_species; species++)
    {
        this->animal_arrs[species] = new Animal *[2]; /* Monkeys, Otters, Sloths */
        this->arr_lens[species] = 2;
        this->arr_nums[species] = 0;
        this->expenses[species] = 0;
        this->revenues[species] = 0;
    }
    add_animal(new Monkey(false, "Mankey (born)"));
    add_animal(new Monkey(true));
    add_animal(new Otter());
}

Zoo::~Zoo()
{
    for (int species = 0; species < this->num_species; species++)
    {
        for (int animal = 0; animal < this->arr_nums[species]; animal++)
        {
            delete this->animal_arrs[species][animal];
        }
        delete[] this->animal_arrs[species];
    }
    delete[] this->animal_arrs;
    delete[] this->arr_lens;
    delete[] this->arr_nums;
    delete[] this->revenues;
    delete[] this->expenses;
}

/*                                                                                      -
 *  Function:   		Zoo::game_setup()
 *  Description:		a
 *  Returns:            _ as a void
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    a
 */
void Zoo::game_setup()
{
}

/*                                                                                      -
 *  Function:   		Zoo::day_setup()
 *  Description:		a
 *  Returns:            _ as a void
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    a
 */
void Zoo::day_setup()
{
    this->day_num++;
    update_base_food();
    update_rev_exp();
}

void Zoo::update_base_food()
{
    std::mt19937 rng(time(NULL));
    std::uniform_int_distribution<int> gen(.75 * this->base_food_cost, 1.25 * base_food_cost);
    this->base_food_cost = gen(rng);
}

void Zoo::update_rev_exp(bool paying_for_meds)
{
    // Generate revenues and expenses
    for (int species = 0; species < this->num_species; species++)
    {
        this->revenues[species] = 0;
        this->expenses[species] = 0;
        for (int animal = 0; animal < this->arr_nums[species]; animal++)
        {
            this->revenues[species] +=
                this->animal_arrs[species][animal]->get_revenue();

            this->revenues[species] +=
                this->animal_arrs[species][animal]->get_food_cost_mult() * base_food_cost;
        }
    }
}

// Returns whether the game is lost
bool Zoo::end_day(bool paying_for_meds)
{
    int day_total = 0;
    update_rev_exp(paying_for_meds);
    for (int species = 0; species < this->num_species; species++)
    {
        day_total += this->revenues[species] - this->expenses[species];

        // Kill unmedicated animals of species
        for (int animal = 0; animal < this->arr_nums[species]; animal++)
        {
            this->animal_arrs[species][animal]->day_passes();

            if (!paying_for_meds && this->animal_arrs[species][animal]->get_is_sick())
            {
                remove_animal(species, animal);
            }
        }
    }

    this->funds += day_total;

    if (funds <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*                                                                                      -
 *  Function:   		Zoo::display()
 *  Description:		a
 *  Returns:            _ as a void
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    a
 */
void Zoo::display()
{
    for (int i = 0; i < this->num_species; i++)
    {
        for (int j = 0; j < this->arr_nums[i]; j++)
        {
            this->animal_arrs[i][j]->print_all();
        }
    }
}

/*                                                                                      -
 *  Function:   		Zoo::day()
 *  Description:		a
 *  Returns:            Whether game is over as a bool
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    
 */
bool Zoo::day()
{
    return false;
}

void Zoo::add_animal(Animal *new_animal)
{
    int species_index;
    std::string species = new_animal->get_species();
    if (species == "Monkey")
    {
        species_index = 0;
    }
    else if (species == "Otter")
    {
        species_index = 1;
    }
    else if (species == "Sloth")
    {
        species_index = 2;
    }

    // Grow array if needed
    if (this->arr_nums[species_index] + 1 >= this->arr_lens[species_index])
    {
        grow_array(species_index);
    }

    // Add Animal to the array
    this->animal_arrs[species_index][this->arr_nums[species_index]] = new_animal;
    this->arr_nums[species_index]++;
}

void Zoo::grow_array(int species_index)
{
    // Store current animals
    Animal **temp_arr = new Animal *[this->arr_nums[species_index]];
    for (int animal = 0; animal < this->arr_nums[species_index]; animal++)
    {
        temp_arr[animal] = this->animal_arrs[species_index][animal];
    }

    // Delete and create new array (double length)
    this->arr_lens[species_index] *= 2;
    delete[] this->animal_arrs[species_index];
    this->animal_arrs[species_index] = new Animal *[this->arr_lens[species_index]];

    // Fill new array
    for (int animal = 0; animal < this->arr_nums[species_index]; animal++)
    {
        this->animal_arrs[species_index][animal] = temp_arr[animal];
    }

    // Cleanup
    delete[] temp_arr;
}

void Zoo::remove_animal(int species_index, int animal_index)
{
    delete this->animal_arrs[species_index][animal_index];
    for (int i = animal_index; i < this->arr_nums[species_index] - 1; i++)
    {
        this->animal_arrs[species_index][animal_index] =
            this->animal_arrs[species_index][animal_index + 1];
    }
    this->arr_nums[species_index]--;
}