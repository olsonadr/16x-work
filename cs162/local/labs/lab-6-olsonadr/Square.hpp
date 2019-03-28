#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

class Square : public Rectangle
{
    public:
        // Constructor
        Square(std::string color,
               int side_length)
            : Rectangle("Square", color, side_length, side_length) {}

        // Accessors
        int get_side_length() { return this->get_width(); }

        // Mutators
        void set_side_length(int new_length);

        // Overloaded
        void set_width(int new_length) { set_side_length(new_length); }
        void set_height(int new_length) { set_side_length(new_length); }
};

#endif
