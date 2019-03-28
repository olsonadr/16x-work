/*
 * Open Space Class Header
 */

#ifndef OPEN_SPACE
#define OPEN_SPACE

#include "MazeLocation.hpp"

class OpenSpace : public MazeLocation
{
    protected:
        bool has_start, has_end, has_player,
             has_ta, has_instructor, has_p_skill;

    public:
        OpenSpace()
            : has_start(false), has_end(false),
              has_ta(false), has_instructor(false),
              has_player(false), has_p_skill(false) {}


        bool is_occupiable() { return true; }

        bool get_has_start()	    { return this->has_start;	    }
        bool get_has_end()	    { return this->has_end;	    }
        bool get_has_player()	    { return this->has_player;	    }
        bool get_has_ta()	    { return this->has_ta;	    }
        bool get_has_instructor()   { return this->has_instructor;  }
        bool get_has_p_skill()	    { return this->has_p_skill;	    }

        void set_has_start(bool val)	    { this->has_start	    = val; }
        void set_has_end(bool val)	    { this->has_end	    = val; }
        void set_has_player(bool val)	    { this->has_player	    = val; }
        void set_has_ta(bool val)	    { this->has_ta	    = val; }
        void set_has_instructor(bool val)   { this->has_instructor  = val; }
        void set_has_p_skill(bool val)	    { this->has_p_skill	    = val; }

        char get_display_character();
        void reset_contents();
	void reset_moving_contents();
};

#endif
