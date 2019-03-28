/*
 *  Program:		BufferToggle.cpp - BufferToggle Class Implementation File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The implementation of the BufferToggle class described in
 *                      BufferToggle.hpp, it'll be used to disable the buffering
 *                      of input in the program.
 */

#include "BufferToggle.hpp"

/* Disables buffered input */
void BufferToggle::off()
{
    tcgetattr(STDIN_FILENO, &t);	    // Get current terminal info
    t.c_lflag &= ~ICANON;		    // Manipulate flag bits
    tcsetattr(STDIN_FILENO, TCSANOW, &t);   // Apply new settings
}


/* Enables buffered input */
void BufferToggle::on()
{
    tcgetattr(STDIN_FILENO, &t);	    // Get current terminal info
    t.c_lflag |= ICANON;		    // Manipulate flag bits
    tcsetattr(STDIN_FILENO, TCSANOW, &t);   // Apply new settings
}
