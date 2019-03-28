/*
 *  Program:		BufferToggle.hpp - BufferToggle Class Header File
 *  Author:		Nick Olson
 *  Date:		02/21/19
 *  Description:	The header file of the BufferToggle class. Lists all include
 *                      statements and function prototypes for BufferToggle class.
 */

#ifndef BUFFER_TOGGLE_HPP
#define BUFFER_TOGGLE_HPP

#include <unistd.h>
#include <termios.h>

class BufferToggle
{
    private:
        struct termios t;

    public:
        void off();
        void on();
};

#endif
