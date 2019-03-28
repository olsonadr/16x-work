/*
 *  Program:		Gold.cpp - Gold Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Gold class described in
 *                      Gold.hpp, objects of which are Events that represent
 *                      the hoard of the Wumpus' Gold and one of the primary
 *                      objectives of the game.
 */

#include "Gold.hpp"

/*                                                                                      -
 * Function:		Gold::handle_player()
 * Description:		Takes a pointer to the current Player object and manipulates the
 *			    Player as much as it can as it should, returning whether the
 *			    game is definitely over because of this. For Gold, this just
 *			    sets the flag that the Player has found the Gold.
 * Parameters:		Player * p:
 *			    A pointer to the Player object currently used in the Game.
 * Returns:		Whether the Game is definitely over because of this handling.
 * Pre-conditions:	The Player is instantiated and the Game has begun.
 * Post-conditions:	The Player is modified and GAME_NOT_OVER has been returned to
 *			    the Game flow.
 */
bool Gold::handle_player(Player * p)
{
    p->set_has_gold(true);
    return GAME_NOT_OVER;
}


/*                                                                                      -
 * Function:		Gold::get_enter_text()
 * Description:		Returns the flavor text that should be delivered to the user when
 *			    they enter the room containing this event. The string is for-
 *			    matted to be centered in an Alert.
 * Return Value:	The flavor text as an std::string.
 * Pre-Conditions:	Usually, the user has just entered the Room containing this.
 * Post-Conditions:	The flavor text has been removed.
 */
std::string Gold::get_enter_text()
{
    return "     You found the Gold of the Wumpus!      \nIf the Wumpus is killed, you can leave flee!\n               Press enter...\0";
}
