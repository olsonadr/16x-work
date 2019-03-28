#include "Square.hpp"

void Square::set_side_length(int new_length)
{
    Rectangle::set_width(new_length);
    Rectangle::set_height(new_length);
}
