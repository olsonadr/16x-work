#include "Zoo.hpp"

int main()
{
    Zoo * z = new Zoo;
    z->game_setup();

    bool keep_going = true;

    while (keep_going)
    {
        bool game_is_over = z->day();

        if (game_is_over)
        {
            keep_going = false;
        }
    }

    delete z;
    return 0;
}
