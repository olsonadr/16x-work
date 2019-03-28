/*
 *  Program:		Wumpus.cpp - Wumpus Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Wumpus class described in
 *                      Wumpus.hpp, objects of which represent an Event for
 *                      the Wumpus, which kills the Player when encountered.
 */

#include "Wumpus.hpp"

/*                                                                                      -
 * Function:		Wumpus::handle_player()
 * Description:		Takes a pointer to the current Player object and manipulates the
 *			    Player as much as it can as it should, returning whether the
 *			    game is definitely over because of this. For Wumpus, returns
 *			    that the Game should be over as the Player has died.
 * Parameters:		Player * p:
 *			    A pointer to the Player object currently used in the Game.
 * Returns:		Whether the Game is definitely over because of this handling.
 * Pre-conditions:	The Player is instantiated and the Game has begun.
 * Post-conditions:	GAME_IS_OVER has been returned to the Game flow (true).
 */
bool Wumpus::handle_player(Player * p)
{
    return GAME_IS_OVER;
}


/*                                                                                      -
 * Function:		Wumpus::get_enter_text()
 * Description:		Returns the flavor text that should be delivered to the user when
 *			    they enter the room containing this event. The string is for-
 *			    matted to be centered in an Alert.
 * Return Value:	The flavor text as an std::string.
 * Pre-Conditions:	Usually, the user has just entered the Room containing this.
 * Post-Conditions:	The flavor text has been removed.
 */
std::string Wumpus::get_enter_text()
{
    return "      You've found the horrid Wumpus!\nIt wakes up and eats you. Get hecked, nerd.\n               Press enter...\0";
}
