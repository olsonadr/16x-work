/*
 *  Program:		Player.hpp - Player Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the Player class, lists all include
 *                      statements and function prototypes for Player class,
 *                      which represents the user's avatar in the game.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifndef GAME_IS_OVER
#define GAME_IS_OVER true
#endif
#ifndef GAME_NOT_OVER
#define GAME_NOT_OVER false
#endif

#include <string>

class Player
{
    private:
        int x_pos;
        int y_pos;
        int cave_width;
        int cave_height;
        int n_arrows;
        bool has_gold;
        bool has_killed_wumpus;

    public:
        // Constructor
        Player()
            : x_pos(0), y_pos(0),
              cave_width(0), cave_height(0),
              n_arrows(3), has_gold(false),
              has_killed_wumpus(false) {}

        // Accessors
        int get_x_pos()			{ return this->x_pos; }
        int get_y_pos()			{ return this->y_pos; }
        int get_n_arrows()		{ return this->n_arrows; }
        bool get_has_gold()		{ return this->has_gold; }
        bool get_has_killed_wumpus()	{ return this->has_killed_wumpus; }

        // Mutators
        void reset_arrows()			{ this->n_arrows = 3; }
        void set_has_gold(bool val)		{ this->has_gold = val; }
        void set_has_killed_wumpus(bool val)	{ this->has_killed_wumpus = val; }
        void move(std::string direction);
        void set_dims(int w, int h);
        void move_to(int x, int y);
        bool shoot();
};

#endif
