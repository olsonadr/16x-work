/*
 *  Program:		Player.cpp - Player Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Player class described in
 *                      Player.hpp, objects of which represent the user's
 *                      avatar, which is moved around and controlled.
 */

#include "Player.hpp"

/*                                                                                      -
 * Function:		Player::move()
 * Description:		Moves the Player in the direction passed, if and only if the step
 *			    would not push them out of bounds of the cave.
 * Parameters:		std::string direction:
 *			    The direction to move as a string (N, S, E, W for up, down,
 *			    right, left, respectively).
 * Pre-conditions:	All fields have been instantiated, the cave dimensions have been
 *			    passed to the Player using the set_dims() function.
 * Post-conditions:     The Player has been moved in the passed direction if there is a
 *			    Room in that direction.
 */
void Player::move(std::string direction)
{
    if (direction == "N")
    {
        if (this->y_pos > 0)
        {
            /* In bounds */
            this->y_pos -= 1;
        }
    }
    else if (direction == "S")
    {
        if (this->y_pos < this->cave_height - 1)
        {
            /* In bounds */
            this->y_pos += 1;
        }
    }
    else if (direction == "W")
    {
        if (this->x_pos > 0)
        {
            /* In bounds */
            this->x_pos -= 1;
        }
    }
    else if (direction == "E")
    {
        if (this->x_pos < this->cave_width - 1)
        {
            /* In bounds */
            this->x_pos += 1;
        }
    }
}


/*                                                                                      -
 * Function:		Player::set_dims()
 * Description:		Takes and stores the current dimensions of the cave such that the
 *			    Player can accurately handle movement.
 * Parameters:		int cave_w:
 *			    The width (cols) of the current cave.
 *			int cave_h:
 *			    The height (rows) of the current cave.
 * Pre-conditions:	All fields have been instantiated. cave)w > 0 and cave_h > 0.
 * Post-conditions:     The dimensions of the current cave have been stored.
 */
void Player::set_dims(int cave_w, int cave_h)
{
    this->cave_width = cave_w;
    this->cave_height = cave_h;
}


/*                                                                                      -
 * Function:		Player::move_to()
 * Description:		The Player has been moved to the passed coordinates, doesn't stop
 *			    the Player from moving out of bounds. Used for Bats handling
 *			    and randomizing position at beginning of Game.
 * Parameters:		int x:
 *			    The x position (col) to move the Player to.
 *			int y:
 *			    The y position (row) to move the Player to.
 * Pre-conditions:	All fields have been instantiated. The passed position is valid
 *			    and in the bounds of the cave (please).
 * Post-conditions:     The player has been moved to the passed position.
 */
void Player::move_to(int x, int y)
{
    this->x_pos = x;
    this->y_pos = y;
}


/*                                                                                      -
 * Function:		Player::shoot()
 * Description:		Decrements the number of arrows the Player has, returns whether
 *			    this shot would entail the end of the Game (if the Player has
 *			    not yet killed the Wumpus).
 * Returns:		If the Player is out of arrows (and Game might be over).
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:	Number of arrows have been decremented and whether this means the
 *			    Game could be over because of this action.
 */
bool Player::shoot()
{
    this->n_arrows--;
    return (n_arrows > 0) ? (GAME_NOT_OVER) : (GAME_IS_OVER);
}
