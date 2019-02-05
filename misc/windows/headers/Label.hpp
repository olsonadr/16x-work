/*
 *  Label class, which is the lowest level of Element. Each Label is a
 *  C-style string with a position, although it can be initialized as
 *  vertical (filled with \n after each character for vertical printing).
 */

#ifndef LABEL_HPP
#define LABEL_HPP

#include "Element.hpp"

class Label : public Element
{
    protected:
      char *str;
      int len;
      bool is_vertical;

    public:
      // Constructors + Destructors
      Label(int x = 0, int y = 0,
            const char *str = "",
            bool is_vertical = false); /* Set Label, int coords */

      Label(const Label &old_label); /* Copy constructor */

      void operator=(const Label &old_label); /* Overloaded assignment */

      // Accessors + Mutators
      void set_str(const char *new_val,
                   bool is_vertical = false);

      char *get_str() { return this->str; }

      int get_len() { return this->len; }

      bool get_is_vertical() { return this->is_vertical; }
};

#endif