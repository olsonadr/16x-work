/*
 * IntrepidStudent Class Header File
 */

#ifndef INTREPID_STUDENT_HPP
#define INTREPID_STUDENT_HPP

#include <iostream>
#include "MazePerson.hpp"
#include "Console.hpp"

class IntrepidStudent : public MazePerson
{
    private:
        int n_skills;
        Console * my_console;
        bool has_console;


    public:
        IntrepidStudent()
            : MazePerson(0, 0, true),
              n_skills(0), has_console(false),
              my_console(nullptr) {}

        std::string get_type() { return "IntrepidStudent"; }

        int get_n_skills()  { return this->n_skills; }
        void use_skill()    { this->n_skills--; }
        void add_skill()    { this->n_skills++; }
        void take_skills()  { this->n_skills = 0; }

        char get_move();
        void move_to(int, int);
        bool rand_start()   { return false; }

        void give_console(Console * my_console);
};

#endif
