/*
 * MazePerson Class Header File
 */

#ifndef MAZE_PERSON_HPP
#define MAZE_PERSON_HPP

#include <iostream>
#include <random>

class MazePerson
{
    protected:
        int x_pos, y_pos;
        bool has_moved;

    public:
        MazePerson(int x, int y, bool h) : x_pos(x), y_pos(y), has_moved(h) {}

        int	get_x_pos()	    { return this->x_pos; }
        int	get_y_pos()	    { return this->y_pos; }
        bool	get_has_moved()	    { return this->has_moved; }
        void	reset_has_moved()   { this->has_moved = false; }

        virtual std::string get_type() = 0;
        virtual char get_move() = 0;
        virtual void move_to(int new_x, int new_y) = 0;
        virtual bool rand_start() = 0;
};

#endif
