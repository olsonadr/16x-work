/*
 * Open Space Class Header
 */

#ifndef OPEN_SPACE
#define OPEN_SPACE

#include "MazeLocation.hpp"

class OpenSpace : public MazeLocation
{
    protected:
        bool has_start;
        bool has_end;
        bool has_player;

    public:
        OpenSpace() : has_start(false), has_end(false), has_player(false) {}

        bool is_occupiable();
        char get_display_character();
	bool get_has_start();
	bool get_has_end();
	bool get_has_player();

        void set_has_start(bool);
        void set_has_end(bool);
        void set_has_player(bool);
        void reset_contents();
};

#endif
