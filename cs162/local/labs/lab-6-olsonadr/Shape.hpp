#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class Shape
{
    private:
        std::string name;
        std::string color;

    public:
        // Constructor
        Shape(std::string name,
              std::string color)
            : name(name),
              color(color) {}

        // Accessors
        std::string get_name() { return this->name; }
        std::string get_color() { return this->color; }

        // Mutators
        void set_color(std::string new_color) { this->color = new_color; }

        // Misc
        float area() { return 0; }

};

#endif
