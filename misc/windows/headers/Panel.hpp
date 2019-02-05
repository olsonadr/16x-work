/*
 *  Panel class, which extends the Element class. It holds an array of
 *  Elements, which it will compile into one 2D array of characters for
 *  rendering of many layered elements (always labels at core).
 */

#ifndef PANEL_HPP
#define PANEL_HPP

#include "Container.hpp"

class Panel : public Container
{
    public:
      // Constructors + Destructors + Operators
      Panel(int x = 0, int y = 0,
            int width = 0, int height = 0); /* Empty members, new Panel */

      Panel(const Panel &old_panel); /* Copy constructor */

      void operator=(const Panel &old_panel); /* Overloaded assignment */

      ~Panel();
};

#endif