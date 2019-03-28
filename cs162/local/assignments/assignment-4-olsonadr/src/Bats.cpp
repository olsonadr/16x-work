/*
 *  Program:		Bats.cpp - Bats Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Bats class described in
 *                      Bats.hpp, objects of which represent Events that
 *                      are "Super Bats" that carry the Player to some
 *			random room when they're encountered.
 */

#include "Bats.hpp"

/*                                                                                      -
 * Constructor:		Bats::Bats()
 * Description:		The primary constructor for the Bats class, takes and stores the
 *			    dimensions of the current cave.
 * Parameters:		int cave_w:
 *			    The width (cols) of the current cave.
 *			int cave_h:
 *			    The height (rows) of the current cave.
 * Post-conditions:	All fields have been instantiated.
 */
Bats::Bats(int cave_w, int cave_h)
    : cave_width(cave_w),
      cave_height(cave_h) {}


/*                                                                                      -
 * Function:		Bats::handle_player()
 * Description:		Takes a pointer to the current Player object and moves the Player
 *			    to a random room in the cave, returning that the game is not
 *			    definitely over because of this (the new room is handled in
 *			    the Game class).
 * Parameters:		Player * p:
 *			    A pointer to the Player object currently used in the Game.
 * Returns:		That the Game is not definitely over because of this handling.
 * Pre-conditions:	The Player is instantiated and the Game has begun, the Bats has
 *			    been constructed with the correct cave dimensions.
 * Post-conditions:	The Player has been moved and GAME_NOT_OVER has been returned to
 *			    the Game flow.
 */
bool Bats::handle_player(Player * p)
{
    // Generate random coordinates
    int rand_x, rand_y;
    rand_x = rand() % cave_width;
    rand_y = rand() % cave_height;

    // Apply this to the Player
    p->move_to(rand_x, rand_y);

    // Return that the game isn't necessarily over
    return GAME_NOT_OVER;
}


/*                                                                                      -
 * Function:		Bats::get_enter_text()
 * Description:		Returns the flavor text that should be delivered to the user when
 *			    they enter the room containing this event. The string is for-
 *			    matted to be centered in an Alert.
 * Return Value:	The flavor text as an std::string.
 * Pre-Conditions:	Usually, the user has just entered the Room containing this.
 * Post-Conditions:	The flavor text has been removed.
 */
std::string Bats::get_enter_text()
{
    return "   You run into some Super Bats!\nYou are carried off to another room!\n          Press enter...\0";
}
