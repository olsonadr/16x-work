/*
 *  Program:		Zoo.cpp - Zoo Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/04/19
 *  Description:	The implementation of the Zoo class described in
 *                      Zoo.hpp, objects of which represent...
 */

#include "Zoo.hpp"

#define MONKEY_I 0
#define OTTER_I 1
#define SLOTH_I 2


/*                                                                                      -
 *  Constructor:	Zoo::Zoo()
 *  Description:	Default constructor for Zoo class, initializes all fields to the
 *			    default values and nothing else.
 *  Pre-conditions:     No fields have been instantiated.
 *  Post-conditions:    All fields have been instantiated.
 */
Zoo::Zoo()
    : num_species(3), day_num(0), funds(100000),
      base_food_cost(50), boom_rev(0),
      prev_food_quality(1), curr_food_quality(1),
      any_sick(false), rng(time(NULL)),
      name_gen(0, 7), food_gen(75, 125),
      species_gen(0, 2), low_special_gen(0, 9),
      reg_special_gen(0, 7), sup_special_gen(0, 5)
{
    this->animal_arrs = new Animal ** [this->num_species];
    this->arr_lens = new int[this->num_species];
    this->arr_nums = new int[this->num_species];
    this->revenues = new int[this->num_species];
    this->expenses = new int[this->num_species];

    for (int species = 0; species < this->num_species; species++)
    {
        this->animal_arrs[species] = new Animal *[2]; /* Monkeys, Otters, Sloths */
        this->arr_lens[species] = 2;
        this->arr_nums[species] = 0;
        this->expenses[species] = 0;
        this->revenues[species] = 0;
    }
}


/*
 * Destructor:		Zoo::~Zoo()
 * Description:		The overriden constructor for the Zoo class, frees all memory that
 *			    Zoo has allocated on the heap.
 * Pre-Conditions:	All fields instantiated, Zoo is leaving scope.
 * Post-Conditions:	All memory has been free'd.
 */
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
 *  Function:		Zoo::game_setup()
 *  Description:	All logic that must occur to make the Zoo ready for gameplay, this
 *			    will include handling the UI when that is implemented, also
 *			    shows the opening screen.
 *  Pre-conditions:     Zoo has been created but not setup yet.
 *  Post-conditions:    Zoo is ready for gameplay.
 */
void Zoo::game_setup()
{
    system("CLS");
    system("clear");
    opening_screen();
}


/*                                                                                      -
 *  Function:		Zoo::day_setup()
 *  Description:	The logic that must occur before a day occurs (resetting fields,
 *			    handles special event, updates food costs, etc).
 *  Pre-conditions:     All fields have been instantiated. This has not been called for
 *			    this day yet, day has not been called for this day yet.
 *  Post-conditions:    The Zoo is ready for the rest of the logic of a day.
 */
void Zoo::day_setup()
{
    system("CLS");
    system("clear");
    this->curr_food_quality = 1;
    this->boom_rev = 0;
    this->any_sick = false;
    special_event();
    update_base_food();
    update_rev_exp();
}

/*
 * Function:		Zoo::update_base_food()
 * Description:		Sets the base food cost to some percentage of what it was prior
 *			    (between 75% and 125%).
 * Pre-Conditions:	All fields instantiated. Called from within day_setup().
 * Post-Conditions:	Base food cost is updated and ready for new day.
 */
void Zoo::update_base_food()
{
    this->base_food_cost = (this->base_food_cost * food_gen(rng)) / 100;
}


/*
 * Function:		Zoo::update_rev_exp(...)
 * Description:		Updates the revenues and expenses arrays with the current correct
 *			    values, taking into account whether they're paying for meds
 *			    and whether it's a attendance boom, etc.
 * Parameters:		bool paying_for_meds:
 *			    Whether the user is paying for medication that day.
 * Pre-Conditions:	All fields instantiated, boom_rev is already accurate for day,
 *			    which is handled in special_event().
 * Post-Conditions:	revenues and expenses are accurate to current day and choices.
 */
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

            this->expenses[species] +=
                this->animal_arrs[species][animal]->get_food_cost_mult() * this->base_food_cost;

            if (this->animal_arrs[species][animal]->get_is_sick())
            {
                if (paying_for_meds)
                {
                    this->expenses[species] +=
                        this->animal_arrs[species][animal]->get_cost() / 2;
                }
            }
        }
    }

    this->revenues[MONKEY_I] += this->boom_rev; /* For Monkeys */
}


/*
 * Function:		Zoo::end_day(...)
 * Description:		Handles logic that occurs at the end of a given day, making the
 *			    user's financial decisions permanent, updating totals, killing
 *			    unmedicated animals, and returning whether the user lost the
 *			    game due to bankruptcy that day.
 * Parameters:		bool paying_for_meds:
 *			    Whether the user is paying for medication that day.
 * Return Value:	Whether the player lost as a boolean value.
 * Pre-Conditions:	All fields instantiated, called from day(), and all inputs were
 *			    succesful inside day().
 * Post-Conditions:	All choices of that day have been committed, returned whether the
 *			    user has lost.
 */
bool Zoo::end_day(bool paying_for_meds)
{
    this->prev_food_quality = this->curr_food_quality;
    this->day_num++;

    int day_total = 0;
    update_rev_exp(paying_for_meds);

    for (int species = 0; species < this->num_species; species++)
    {
        day_total += this->revenues[species] - this->expenses[species];

        // Kill unmedicated animals of species
        for (int animal = 0; animal < this->arr_nums[species]; animal++)
        {
            this->animal_arrs[species][animal]->day_passes();

            if (this->animal_arrs[species][animal]->get_is_sick())
            {
                if (paying_for_meds)
                {
                    this->animal_arrs[species][animal]->medicate();
                }
                else
                {
                    remove_animal(species, animal);
                }
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
 *  Function:		Zoo::display()
 *  Description:	Displays UI of Zoo tycoon (currently prints out information about
 *			    the current day and its revenues, etc.
 *  Pre-conditions:     All fields have been instantiated.
 *  Post-conditions:    All pertinent information has been displayed.
 */
void Zoo::display()
{
    system("CLS");
    system("clear");

    int total_rev = 0;
    int total_exp = 0;
    int total_net = 0;

    for (int i = 0; i < this->num_species; i++)
    {
        total_rev += this->revenues[i];
        total_exp -= this->expenses[i];
    }

    total_net = total_rev + total_exp;
    char buff[50];
    sprintf(buff, "\nDay: %37d\0", this->day_num);
    output(buff);
    output("------------------------------------------*");
    sprintf(buff, "Funds: %35d\0", this->funds);
    output(buff);
    sprintf(buff, "Cost of Food: %28d\0", this->base_food_cost);
    output(buff);
    sprintf(buff, "Revenues: %32d\0", total_rev);
    output(buff);
    sprintf(buff, "Expenses: %32d\0", total_exp);
    output(buff);
    sprintf(buff, "Net: %37d\n\0", total_net);
    output(buff);
}

/*                                                                                      -
 *  Function:		Zoo::day()
 *  Description:	Handles all logic important to and input taken during current day.
 *  Returns:            Whether game is over as a bool.
 *  Pre-conditions:     All fields have been instantiated, game_setup() has been called.
 *  Post-conditions:	All decisions have been comitted, whether they lost is returned.
 */
bool Zoo::day()
{
    day_setup();
    display();

    // Medication
    bool paying_for_meds = false;

    if (this->any_sick)
    {
        display();
        paying_for_meds = get_bool_input("Do you pay for medication (y or n)?");
        output(" ");
    }

    update_rev_exp(paying_for_meds);

    if(paying_for_meds == true)
    {
	int total_exp = 0;
	for(int i = 0; i < this->num_species; i++)
	{
	    total_exp += this->expenses[i];
	}

	char buff[50];
	sprintf(buff, "New Expenses: %28d\0", total_exp);
	output("New Expenses: ");
    }

    // Food
    bool keep_going = true;

    while (keep_going)
    {
        output("What food do you feed your animals?");
        std::string in = input("(C)heap .5x, (R)egular 1x, (P)remium 2x");
        output(" ");

        if (in.length() < 1)
        {
            output("**ERROR: Input may not be blank!**\n");
        }
        else
        {
            in = std::tolower(in[0]);

            if (in != "c" && in != "r" && in != "p" && in != "q")
            {
                output("**ERROR: Invalid input!**\n");
            }
            else
            {
                keep_going = false;

                if (in == "c")
                {
                    /* Cheap food */

                    this->curr_food_quality = 0;
                }
                else if (in == "r")
                {
                    /* Regular food */

                    this->curr_food_quality = 1;
                }
                else if (in == "p")
                {
                    /* Premium food */

                    this->curr_food_quality = 2;
                }
                else if (in == "q")
                {
                    this->curr_food_quality = 1;
                    end_day();
                    game_over_screen();
                    return true;
                }
            }
        }
    }

    update_rev_exp(paying_for_meds);
    //display();

    // End day, check for game over
    bool game_over = end_day(paying_for_meds);

    if (game_over)
    {
        game_over_screen();
        return true;
    }

    // Buy new animals
    if (get_bool_input("Go to store after hours (y or n)?"))
    {
        buy_animal();
    }
    else
    {
	output(" ");
    }

    output("Press enter to end day...");
    getchar();

    return false;
}


/*
 * Function:		Zoo::add_animal(...)
 * Description:		Adds the passed Animal pointer to the correct Animal array,
 *			    updating other fields as needed, growing the appropriate
 *			    array if it would be over-capacity.
 * Parameters:		Animal * new_animal:
 *			    The new animal to be added to the Zoo.
 * Pre-Conditions:	All fields instantiated.
 * Post-Conditions:	The Animal has been added, memory has been modified as needed.
 */
void Zoo::add_animal(Animal * new_animal)
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


/*
 * Function:		Zoo::grow_array(...)
 * Description:		Grows the Animal array at the passed species index (doubles
 *			    its size in memory. This should only be called from add
 *			    when adding a new Animal would put that species' index
 *			    over capacity. This is meant to mimic vectors.
 * Parameters:		int species_index:
 *			    The index of the species whose array will be grown.
 * Pre-Conditions:	All fields instantiated, specified array must grow.
 * Post-Conditions:	The array at that index has been doubled in length and its
 *			    length is increased as well.
 */
void Zoo::grow_array(int species_index)
{
    //output("GROWING ARRAY " + std::to_string(species_index)); // Debug

    // Store current animals
    Animal ** temp_arr = new Animal *[this->arr_nums[species_index]];

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


/*
 * Function:		Zoo::remove_animal(...)
 * Description:		Removes the specified Animal of the specified species from
 *			    its appropriate array.
 * Parameters:		int species_index:
 *			    The index representing the desired species
 *			int animal_index:
 *			    The index representing the desired Animal
 * Pre-Conditions:	All fields instantiated, there is an Animal at the passed
 *			    indices, arr_nums is accurate.
 * Post-Conditions:	The Animal has been removed and the other Animals have been
 *			    shifted to fill the spot.
 */
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


/*                                                                                      -
 * Function:		Zoo::buy_animal()
 * Description:		Gets user choices about buying an Animal (going to the store),
 *			    adds the purchased Animal to the appropriate array if the
 *			    player has enough money.
 * Pre-Conditions:	All fields instantiated.
 * Post-Conditions:	If the player chose to purchase an Animal and could afford it,
 *			    it has been added to the Zoo.
 */
void Zoo::buy_animal()
{
    std::string monkey_names[8] =
    {
        "Mankey",
        "George",
        "Harambe",
        "Rafiki",
        "Abu",
        "Jack",
        "Donkey",
        "Roger"
    };
    std::string otter_names[8] =
    {
        "Daxter",
        "Lottie",
        "Marlene",
        "Eddie",
        "James",
        "Randall",
        "Sarah",
        "Steve"
    };
    std::string sloth_names[8] =
    {
        "Buttercup",
        "Bad Josh",
        "Gus",
        "Chubbs",
        "Dozer",
        "Droopy",
        "Jeremy",
        "Scott"
    };

    bool keep_going = true;

    while (keep_going)
    {
        output("\nChoose species or 'cancel':");
        output("(M)onkey  ($15,000)\n(O)tter    ($5,000)\n(S)loth    ($2,000)");
        std::string in = input(">> ");
        output(" ");

        if (in.length() < 1)
        {
            output("**ERROR: Input may not be blank!**\n");
        }
        else
        {
            in = std::tolower(in[0]);

            if (in == "e")
            {
                keep_going = false;
            }
            else if (in != "m" && in != "s" && in != "o")
            {
                output("**ERROR: Invalid input!**\n");
            }
            else
            {
                Animal * purchased;

                if (in == "m")
                {
                    purchased = new Monkey(true, monkey_names[name_gen(rng)]);
                }
                else if (in == "s")
                {
                    purchased = new Sloth(true, sloth_names[name_gen(rng)]);
                }
                else if (in == "o")
                {
                    purchased = new Otter(true, otter_names[name_gen(rng)]);
                }

                if (this->funds < purchased->get_cost())
                {
                    output("Insufficient funds for ", purchased->get_name(),
                           " the ", purchased->get_species(), "!\n");

                    delete purchased;
                }
                else
                {
                    this->funds -= purchased->get_cost();
                    add_animal(purchased);
                    keep_going = false;
                    output("You have purchased ", purchased->get_name(),
                           " the ", purchased->get_species(), "!\n");
                }
            }
        }
    }
}


/*                                                                                      -
 * Function:		Zoo::output(...)
 * Description:		These two output definitions handle output by taking any number of
 *			    arguments separated by commas. If there are more than one arg-
 *			    uments, the second is called, which recursively calls itself
 *			    until there is only one argument called, at which point the
 *			    first executes, thus outputing all of them.
 * Parameters:		const Head & first:
 *			    The first argument passed.
 *			const Tail & ... args:
 *			    All arguments following the first.
 * Pre-Conditions:	The arguments are strings.
 * Post-Conditions:	The arguments have all been printed.
 */
template <typename Head>
void Zoo::output(const Head & first)
{
    std::cout << first << std::endl;
}

template <typename Head, typename... Tail>
void Zoo::output(const Head & first, const Tail & ... args)
{
    std::cout << first;
    output(args...);
}


/*                                                                                      -
 * Function:		Zoo::input(...)
 * Description:		Takes user input after output()-ing a passed prompt string.
 * Parameters:		std::string prompt:
 *			    The prompt for the user before getting their input.
 * Return Value:	The user's response as an std::string.
 * Post-Conditions:	The user's input has been returned.
 */
std::string Zoo::input(std::string prompt)
{
    std::string result;

    if (prompt[prompt.length() - 1] == ' ')
    {
        std::cout << prompt;
    }
    else
    {
        std::cout << prompt << std::endl
                  << ">> ";
    }

    std::getline(std::cin, result);
    return result;
}


/*                                                                                      -
 * Function:		Zoo::get_bool_input(...)
 * Description:		Gets user input using the input(...) function but only accepting
 *			    y or n results, converting them to a boolean as true or false
 *			    respectively, and asking user to input again if they fail to
 *			    input y or n (case-insensitive).
 * Parameters:		std::string prompt:
 *			    The prompt for the user before taking input.
 * Return Value:	The user's response as a boolean (y => true, n => false).
 * Post-Conditions:	The user's y or n response has been returned.
 */
bool Zoo::get_bool_input(std::string prompt)
{
    bool keep_going = true;
    bool result = true;

    while (keep_going)
    {
        std::string in = input(prompt);

        if (in.length() < 1)
        {
            output("**ERROR: Input may not be blank!**\n");
        }
        else
        {
            in = std::tolower(in[0]);

            if (in == "y")
            {
                result = true;
                keep_going = false;
            }
            else if (in == "n")
            {
                result = false;
                keep_going = false;
            }
            else
            {
                output("**ERROR: Invalid input!**\n");
            }
        }
    }

    return result;
}


/*                                                                                      -
 * Function:		Zoo::special_event()
 * Description:		Handles the random selection and logic of the effects of the
 *			    special events of the game, setting fields to their required
 *			    values for each given event, calling an alert to tell the
 *			    player what happened.
 * Pre-Conditions:	All fields instantiated, the day is being setup, and this method
 *			    has not yet been called for the current day.
 * Post-Conditions:	The fields of the Zoo have been modified to relfect the impacts
 *			    of the randomly selected special event.
 */
void Zoo::special_event()
{
    int rand_num;

    if (this->prev_food_quality == 0)
    {
        /* Low quality food, high chance of sickness */

        rand_num = low_special_gen(rng);
    }
    else if (this->prev_food_quality == 1)
    {
        /* Regular food, regular chance of sickness */

        rand_num = reg_special_gen(rng);
    }
    else
    {
        /* Superior food, lower chance of sickness */

        rand_num = sup_special_gen(rng);
    }

    if (rand_num <= 1)
    {
        /* Baby born */

        int total_animals = 0;

        for (int species = 0; species < this->num_species; species++)
        {
            total_animals += this->arr_nums[species];
        }

        Animal * adults[total_animals];

        int total_adults = 0;

        for (int species = 0; species < this->num_species; species++)
        {
            for (int animal = 0; animal < this->arr_nums[species]; animal++)
            {
                if (this->animal_arrs[species][animal]->get_age_group() == "Adult")
                {
                    adults[total_adults] = this->animal_arrs[species][animal];
                    total_adults++;
                }
            }
        }

        if (total_adults > 0)
        {
            bool keep_going = true;

            std::uniform_int_distribution<int> adult_gen(0, total_adults - 1);
            int rand_adult = adult_gen(rng);

            Animal * target = adults[rand_adult];

            std::string monkey_names[8] =
            {
                "Mankey",
                "George",
                "Harambe",
                "Rafiki",
                "Abu",
                "Jack",
                "Donkey",
                "Roger"
            };
            std::string otter_names[8] =
            {
                "Daxter",
                "Lottie",
                "Marlene",
                "Eddie",
                "James",
                "Randall",
                "Sarah",
                "Steve"
            };
            std::string sloth_names[8] =
            {
                "Buttercup",
                "Bad Josh",
                "Gus",
                "Chubbs",
                "Dozer",
                "Droopy",
                "Jeremy",
                "Scott"
            };

            int rand_num = name_gen(rng);

            for (int i = 0; i < target->get_num_babies(); i++)
            {
                if (target->get_species() == "Monkey")
                {
                    add_animal(new Monkey(false, monkey_names[rand_num]));
                }
                else if (target->get_species() == "Otter")
                {
                    add_animal(new Otter(false, otter_names[rand_num]));
                }
                else if (target->get_species() == "Sloth")
                {
                    add_animal(new Sloth(false, sloth_names[rand_num]));
                }
            }

            std::string message =
                "Day " + std::to_string(this->day_num) + "! " +
                target->get_name() + " the " + target->get_species() +
                " has given birth!\nWe now have " +
                std::to_string(target->get_num_babies()) +
                " new baby " + target->get_species() + "s!";

            alert(message);

        }
        else
        {
            alert("Day " + std::to_string(this->day_num) +
                  "! Nothing special happens today.");
        }
    }
    else if (rand_num > 1 &&
             rand_num <= 3)
    {
        /* Attendance boom */

        alert("Day " + std::to_string(this->day_num) +
              "! There's a boom in attendance today!\nAll monkeys generate extra income.");

        for (int monkey = 0; monkey < this->arr_nums[MONKEY_I]; monkey++)
        {
            this->boom_rev = this->arr_nums[MONKEY_I] *
                             static_cast<Monkey>(this->animal_arrs[MONKEY_I][monkey]).boom_rev();
        }
    }
    else if (rand_num > 3 &&
             rand_num <= 5)
    {
        /* Nothing Occurs */
        alert("Day " + std::to_string(this->day_num) +
              "! Nothing special happens today.");
    }
    else if (rand_num > 5)
    {
        /* Sickness (variable chance) */

        int total_animals = 0;

        for (int species = 0; species < this->num_species; species++)
        {
            total_animals += this->arr_nums[species];
        }

        if (total_animals > 0)
        {
            bool keep_going = true;
            int rand_species, rand_animal;

            while (keep_going)
            {
                rand_species = species_gen(rng);

                if (this->arr_nums[rand_species] > 0)
                {
                    keep_going = false;
                }
            }

            std::uniform_int_distribution<int> animal_gen(0, this->arr_nums[rand_species] - 1);
            rand_animal = animal_gen(rng);
            Animal * target = this->animal_arrs[rand_species][rand_animal];

            target->make_sick();
            this->any_sick = true;
            std::string message =
                "Day " + std::to_string(this->day_num) +
                "! " + target->get_name() +
                " the " + target->get_species() +
                " has fallen ill!\nThey'll die without medication!";
            alert(message);
        }
        else
        {
            alert("Day " + std::to_string(this->day_num) +
                  "! Nothing special happens today.");
        }
    }
}


/*                                                                                      -
 * Function:		Zoo::alert(...)
 * Description:		Alerts the player of some message (using UI hopefully).
 * Parameters:		std::string message:
 *			    The message to be communicated to the player.
 * Pre-Conditions:	All fields instantiated.
 * Post-Conditions:	The user has been alerted and they have hit enter to proceed.
 */
void Zoo::alert(std::string message)
{
    output(" ");
    output(message);
    output("Press enter...");
    output(" ");
    getchar();
}


/*                                                                                      -
 * Function:		Zoo::game_over_screen()
 * Description:		Alerts the user that they have lost, tells them how long they
 *			    survived and their ending funds, waits for enter press.
 * Pre-Conditions:	All fields instantiated, the game has concluded and they ran out
 *			    of funds, this has not been called yet.
 * Post-Conditions:	The user has been informed of their failures.
 */
void Zoo::game_over_screen()
{
    char buff[120];
    sprintf(buff,
            "GAME OVER! You survived for %d days!\nYour final balance was %d.",
            this->day_num, this->funds);
    const char * message = buff;
    alert(message);
}


/*                                                                                      -
 * Function:		Zoo::opening_screen()
 * Description:		Welcomes the user to the game using alert(), waiting for an enter
 *			    press, warning them of the trials to come.
 * Pre-Conditions:	All fields instantiated, the game has just begun, game_setup() is
 *			    the only thing called so far.
 * Post-Conditions:	They're ready for this thing!
 */
void Zoo::opening_screen()
{
    const char * message =
        "*-----------------------------------------*\n#=~ Welcome to Nick Olson's Zoo Tycoon! ~=#\n*-----------------------------------------*";
    alert(message);
}
