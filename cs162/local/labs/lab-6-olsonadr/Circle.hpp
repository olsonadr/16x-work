#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <math.h>
#include "Shape.hpp"

class Circle : public Shape
{
    private:
        int radius;

    public:
        // Constructor
        Circle(std::string color, int radius)
            : Shape("Circle", color),
              radius(radius) {}

        // Accessors
        int get_radius() { return this->radius; }

        // Mutators
        void set_radius(int new_radius) { this->radius = new_radius; }

        // Misc
        float area() { return M_PI * pow(this->radius, 2); }
};

#endif
