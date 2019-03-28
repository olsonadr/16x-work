/*
 *  Program:		Pit.cpp - Pit Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Pit class described in
 *                      Pit.hpp, objects of which represent Events that
 *                      are "Bottomless Pits" which kill the Player if
 *                      they walk over them.
 */

#include "Pit.hpp"

/*                                                                                      -
 * Function:		Pit::handle_player()
 * Description:		Takes a pointer to the current Player object and manipulates the
 *			    Player as much as it can as it should, returning whether the
 *			    game is definitely over because of this. For Pit, this just
 *			    returns that the Game should be over as the Player has died.
 * Parameters:		Player * p:
 *			    A pointer to the Player object currently used in the Game.
 * Returns:		Whether the Game is definitely over because of this handling.
 * Pre-conditions:	The Player is instantiated and the Game has begun.
 * Post-conditions:	GAME_IS_OVER has been returned to the Game flow.
 */
bool Pit::handle_player(Player * p)
{
    return GAME_IS_OVER;
}


/*                                                                                      -
 * Function:		Pit::get_enter_text()
 * Description:		Returns the flavor text that should be delivered to the user when
 *			    they enter the room containing this event. The string is for-
 *			    matted to be centered in an Alert.
 * Return Value:	The flavor text as an std::string.
 * Pre-Conditions:	Usually, the user has just entered the Room containing this.
 * Post-Conditions:	The flavor text has been removed.
 */
std::string Pit::get_enter_text()
{
    return "       You stumbled upon a Bottomless Pit!        \nYou also stumbled into it, so... you're dead now.\n                  Press enter...\0";
}
