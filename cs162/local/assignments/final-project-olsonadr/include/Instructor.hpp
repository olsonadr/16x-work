/*
 * Instructor Class Header File
 */

#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP

#include "MazePerson.hpp"

class Instructor : public MazePerson
{
    private:

    public:
        Instructor() : MazePerson(0, 0, true) {}

        std::string get_type() { return "Instructor"; }

        char get_move();
        void move_to(int, int);
        bool rand_start()   { return false; }
        char give_A()	    { return 'A'; }
};

#endif
