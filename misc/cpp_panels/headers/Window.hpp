/*
 *  Window class. It is a Container that has position (0,0), and is primary
 *  panel used when utilizing this system as it is only kind of container
 *  that has the ability to display the character buffer of its members.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include "sys/ioctl.h"
#include "Container.hpp"

class Window : public Container
{
  protected:
    // Methods
    void resize_terminal();

  public:
    // Constructors + Destructors + Operators
    Window(int width, int height,
           const char *name = "Window")
        : Container(0, 0, width, height, "Window", name) { resize_terminal(); }

    Window(const Window &old_window)
        : Container(old_window) { resize_terminal(); }

    void operator=(const Window &old_window) { Container::operator=(old_window); }

    // Methods
    void print_merged();
};

#endif