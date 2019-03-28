/*
 * Explorer Class Header File
 */

#ifndef EXPLORER_HPP
#define EXPLORER_HPP

#include <random>

class Explorer
{
    private:
	int x_pos, y_pos;

    public:
	Explorer() : x_pos(0), y_pos(0) {}

	int get_x_pos();
	int get_y_pos();

	char get_move();
	void move_to(int, int);
};

#endif
