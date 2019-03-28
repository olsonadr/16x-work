#include <iostream>

#include "Rectangle.hpp"
#include "Square.hpp"
#include "Circle.hpp"

int main()
{
    Square square("Red", 5);
    Circle circle("Blue", 3);
    Rectangle rect("Green", 5, 10);

    std::cout << "square is a "<< square.get_name()
	<< ", is " << square.get_color()
	<< ", has side length of " << square.get_side_length()
	<< ", and has an area of " << square.area()
	<< std::endl;

    std::cout << "circle is a " << circle.get_name()
	<< ", is " << circle.get_color()
	<< ", has radius of " << circle.get_radius()
	<< ", and has an area of " << circle.area()
	<< std::endl;

    std::cout << "rect is a " << rect.get_name()
	<< ", is " << rect.get_color()
	<< ", has width of " << rect.get_width()
	<< ", has height of " << rect.get_height()
	<< ", and has an area of " << rect.area()
	<< std::endl;
    
    return 0;
}
