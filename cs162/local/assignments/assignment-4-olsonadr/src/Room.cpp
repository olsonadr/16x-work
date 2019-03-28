/*
 *  Program:		Room.cpp - Room Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the Room class described in
 *                      Room.hpp, objects of which represent the Rooms in
 *                      the Wumpus's cave. Each can have an Event within.
 *                      Room's handle the memory of their dynamic Events.
 */

#include "Room.hpp"

/*                                                                                      -
 * Function:		Room::handle_player()
 * Description:		If the Room has an Event within it, returns the result of calling
 *			    the Event's handle_player() function, thus impacting the Pla-
 *			    yer and informing the Game whether the Game is over because
 *			    of entering this Room.
 * Parameters:		Player * p:
 *			    A pointer to the current Game's Player.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:     The Event in this room has affected the Player and the Game over
 *			    status has been returned to the Game flow.
 */
bool Room::handle_player(Player * p)
{
    if (this->has_event == true)
    {
        return this->contained_event->handle_player(p);
    }
    else
    {
        return GAME_NOT_OVER;
    }
}


/*                                                                                      -
 * Function:		Room::set_event()
 * Description:		Sets this Room's event to the event at the passed Event pointer.
 *			    As the Room handles the memory of the Events and all Events
 *			    are dynamically allocated, deletes the current Event if there
 *			    is one already in the room.
 * Parameters:		Event * new_event:
 *			    The Event to be added to the Room.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:     The Event has been added to the Room, memory of the old Event has
 *			    been handled if needed.
 */
void Room::set_event(Event * new_event)
{
    if (this->has_event == true)
    {
        delete this->contained_event;
    }

    this->contained_event = new_event;
    this->has_event = true;
}


/*                                                                                      -
 * Function:		Room::clear_event()
 * Description:		Removes the Event from this Room, handling memory.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:     The Room contains no Event, memory has been handled.
 */
void Room::clear_event()
{
    if (this->has_event == true)
    {
        delete this->contained_event;
    }

    this->contained_event = nullptr;
    this->has_event = false;
}


/*                                                                                      -
 * Function:		Room::has_wumpus()
 * Description:		Returns whether this Room contains the Wumpus Event.
 * Returns:		Whether this Room contains the Wumpus Event as a bool.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:	The presence of the Wumpus has been returned.
 */
bool Room::has_wumpus()
{
    if (this->has_event == true &&
            this->contained_event->get_name() == "The Wumpus")
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*                                                                                      -
 * Function:		Room::get_percept()
 * Description:		Returns the "percept" this Room's Event would generate for the
 *			    Player, "No Event" if there is no Event in the Room.
 * Returns:		The percept of this Room's Event as an std::string.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:	The percept of this Room's Event has been returned.
 */
std::string Room::get_percept()
{
    if (this->has_event == true)
    {
        return this->contained_event->get_percept();
    }
    else
    {
        return "No Event";
    }
}


/*                                                                                      -
 * Function:		Room::get_event_name()
 * Description:		Returns the name of this Room's Event if it holds one, "No Event"
 *			    if it does not.
 * Returns:		The name of this Room's Event as an std::string.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:	The name of this Room's Event has been returned.
 */
std::string Room::get_event_name()
{
    if (this->has_event == true)
    {
        return this->contained_event->get_name();
    }
    else
    {
        return "No Event";
    }
}


/*                                                                                      -
 * Function:		Room::get_enter_text()
 * Description:		Returns the enter text of this Room's Event if it holds one
 *			    "No Event" if it does not, just in case
 * Returns:		The enter text of this Room's Event as an std::string.
 * Pre-conditions:	All fields have been instantiated.
 * Post-conditions:	The enter text of this Room's Event has been returned.
 */
std::string Room::get_enter_text()
{
    if (this->has_event == true)
    {
        return this->contained_event->get_enter_text();
    }
    else
    {
        return "No Event";
    }
}
