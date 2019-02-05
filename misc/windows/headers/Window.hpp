/*
 *  Window class, a container that has position (0,0), and is primary
 *  panel used when utilizing this system.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include "Container.hpp"

class Window : public Container
{
public:
  // Constructors + Destructors + Operators
  Window(int width = 0, int height = 0);

  Window(const Window &old_window);

  void operator=(const Window &old_window);

  ~Window();

  // Methods
  void print_merged();
};

#endif