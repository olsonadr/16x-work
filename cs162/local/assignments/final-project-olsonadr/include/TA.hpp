/*
 * TA Class Header File
 */

#ifndef TA_HPP
#define TA_HPP

#include <random>
#include "MazePerson.hpp"

class TA : public MazePerson
{
    private:

    public:
        TA() : MazePerson(0, 0, true) {}

	std::string get_type() { return "TA"; }

        char get_move();
        void move_to(int, int);
        bool rand_start()   { return true; }
        char give_A()	    { return 'A'; }
};

#endif
