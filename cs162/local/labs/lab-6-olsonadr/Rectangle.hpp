#ifndef RECT_HPP
#define RECT_HPP

#include "Shape.hpp"

class Rectangle : public Shape
{
    private:
        int width;
        int height;

    public:
        // Constructor
        Rectangle(std::string color,
                  int width, int height)
            : Shape("Rectangle", color),
              width(width), height(height) {}

        Rectangle(std::string name,
                  std::string color,
                  int width, int height)
            : Shape(name, color),
              width(width), height(height) {}

        // Accessors
        int get_width() { return this->width; }
        int get_height() { return this->height; }

        // Mutators
        void set_width(int new_width) { this->width = new_width; }
        void set_height(int new_height) { this->height = new_height; }

        // Misc
        float area() { return this->width * this->height;}
};

#endif
