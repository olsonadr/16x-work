/*
 * MazeLevel Class Implementation
 */

#include "MazeLevel.hpp"

/*
 * Pre-condition:   maze_file is open and set to top-left corner of the current
 *		    MazeLevel template; the dimensions are accurate.
 * Post-condition:  maze_file is open to the top-left corner of the next MazeLevel
 *		    template or the end of the file, if the file was open and form-
 *		    atted correctly to begin with.
 */
MazeLevel::MazeLevel(std::ifstream & maze_file,
                     int m_width, int m_height)
    : maze_width(m_width), maze_height(m_height), n_people(0)
{
    if (maze_file.is_open() == false)
    {
        throw "Unopened file passed to MazeLevel constructor!";
    }

    // Allocate
    this->locations.resize(m_height);

    for (int row = 0; row < m_height; row++)
    {
        this->locations[row].resize(m_width);

        std::string row_str = "";
        std::getline(maze_file, row_str);

        if (maze_file.fail() || row_str.length() < m_width)
        {
            std::cout << "row_str = " << row_str << std::endl;
            throw "File read error! Bad format!";
        }

        for (int col = 0; col < m_width; col++)
        {
            // Fill
            char curr_char = row_str[col];

            if (curr_char == '#')
            {
                this->locations[row][col] = new Wall();
            }
            else
            {
                OpenSpace * new_open = new OpenSpace();

                if (curr_char == ' ')
                {
                    /* Short-circuit */
                }
                else if (curr_char == '@')
                {
                    new_open->set_has_player(true);
                    new_open->set_has_start(true);
                    this->starting_y = row;
                    this->starting_x = col;
                }
                else if (curr_char == '^')
                {
                    new_open->set_has_end(true);
                }
                else if (curr_char == '%')
                {
                    new_open->set_has_instructor(true);
                }

                this->locations[row][col] = new_open;
            }
        }
    }
}


MazeLevel::~MazeLevel()
{
    for (int row = 0; row < this->maze_height; row++)
    {
        for (int col = 0; col < this->maze_width; col++)
        {
            delete this->locations[row][col];
        }
    }
}


/*
 * Adds a new MazePerson to this level
 */
void MazeLevel::add_person(MazePerson * new_person)
{
    this->people.push_back(new_person);
    this->n_people++;
}


/*
 * Pre-condition:   m_row and m_col must be in bounds, if not, return nullptr
 */
MazeLocation * MazeLevel::get_location(int m_row, int m_col)
{
    if (m_row >= 0 && m_row < this->maze_height
            && m_col >= 0 && m_col < this->maze_width)
    {
        return this->locations[m_row][m_col];
    }
    else
    {
        return nullptr;
    }

}


/*
 * Post-conditions: each MazePerson has had their move gotten and things
 *		    have been adjusted accordingly, a vector containing
 *		    all special moves (those that can't be handled by
 *		    the Level itself) has been returned.
 */
std::vector<char> MazeLevel::get_moves()
{
    bool commit_moves = true;

    std::vector<char> moves;
    std::vector<char> special;

    for (int i = 0; i < this->n_people; i++)
    {
        char move = this->people[i]->get_move();
        moves.push_back(move);

        if (move == '~')
        {
            special.push_back(move);
            commit_moves = false;
            break;
        }
    }

    if (commit_moves)
    {
        for (int i = 0; i < this->n_people; i++)
        {
            char move = moves[i];

            if (move == 'W' || move == 'A'
                    || move == 'S' || move == 'D')
            {
                handle_movement(i, move);
            }
            else
            {
                special.push_back(move);
            }
        }
    }

    return special;
}


/*
 * Pre-condition:   the move being passed in is 'W', 'A', 'S', or 'D',
 *			person_i is in range for people array.
 * Post-condition:  the person has been moved if the movement was valid
 */
void MazeLevel::handle_movement(int person_i, char move)
{
    int target_x = this->people[person_i]->get_x_pos();
    int target_y = this->people[person_i]->get_y_pos();
    int init_x = target_x;
    int init_y = target_y;

    switch (move)
    {
        case 'W':
            target_y -= 1;
            break;

        case 'A':
            target_x -= 1;
            break;

        case 'S':
            target_y += 1;
            break;

        case 'D':
            target_x += 1;
            break;

        default:
            break;
    }

    if (this->locations[target_y][target_x]->is_occupiable() == true)
    {
        this->people[person_i]->move_to(target_x, target_y);
        update_bools(target_x, target_y);

        if (this->locations[init_y][init_x]->is_occupiable() == true)
        {
            update_bools(init_x, init_y);
        }
    }
}


void MazeLevel::display_maze()
{
    std::cout << "#=~" << std::endl;

    for (int row = 0; row < this->maze_height; row++)
    {
        for (int col = 0; col < this->maze_width; col++)
        {
            std::cout << this->locations[row][col]->get_display_character();
        }

        std::cout << std::endl;
    }

    std::cout << "#=~" << std::endl;
}


void MazeLevel::display_maze_occupiable()
{
    std::cout << "#=~" << std::endl;

    for (int row = 0; row < this->maze_height; row++)
    {
        for (int col = 0; col < this->maze_width; col++)
        {
            std::cout << this->locations[row][col]->is_occupiable();
        }

        std::cout << std::endl;
    }

    std::cout << "#=~" << std::endl;
}


void MazeLevel::display_maze_ta(bool corners)
{
    std::cout << "#=~" << std::endl;

    for (int row = 0; row < this->maze_height; row++)
    {
        for (int col = 0; col < this->maze_width; col++)
        {
            bool in_zone = check_intersection(col, row, "TA", 1, corners);

            if (this->locations[row][col]->is_occupiable() == true && in_zone)
            {
                std::cout << ".";
            }
            else
            {
                std::cout << this->locations[row][col]->get_display_character();
            }
        }

        std::cout << std::endl;
    }

    std::cout << "#=~" << std::endl;
}


void MazeLevel::display_maze_instructor()
{
    std::cout << "#=~" << std::endl;

    for (int row = 0; row < this->maze_height; row++)
    {
        for (int col = 0; col < this->maze_width; col++)
        {
            bool in_zone = check_intersection(col, row, "Instructor", 1, true);

            if (this->locations[row][col]->is_occupiable() == true && in_zone)
            {
                std::cout << ".";
            }
            else
            {
                std::cout << this->locations[row][col]->get_display_character();
            }
        }

        std::cout << std::endl;
    }

    std::cout << "#=~" << std::endl;
}


/*
 * Description:	    This is what actually moves the MazePerson's to the correct places,
 *			and places the p_skills, etc. This is separated from the const-
 *			ructor so that the people can be added after the level is cons-
 *			tructed but before it is used. This is essential for the Game.
 *			This can be used to reset the level if the player is caught.
 * Pre-conditions:  The level has been constructed *and* all MazePerson objects that
 *			are required for this current Level have been added using the
 *			add_person() function.
 * Post-conditions: The people on this level have been set to their appropriate initial
 *			positions (randomly for p_skills and TAs). This level is ready
 *			for gameplay.
 */
void MazeLevel::reset_level()
{
    // Clear TAs, Player, and Skills
    for (int row = 0; row < this->locations.size(); row++)
    {
        for (int col = 0; col < this->locations[row].size(); col++)
        {
            MazeLocation * curr_loc = this->locations[row][col];

            if (curr_loc->is_occupiable() == true)
            {
                OpenSpace * curr_open = static_cast<OpenSpace *>(curr_loc);

                if (curr_open->get_has_ta() == true)
                {
                    curr_open->set_has_ta(false);
                }

                if (curr_open->get_has_player() == true)
                {
                    curr_open->set_has_player(false);
                }

                if (curr_open->get_has_p_skill() == true)
                {
                    curr_open->set_has_p_skill(false);
                }
            }
        }
    }

    // New places
    std::vector<int> found_starts_x;
    std::vector<int> found_starts_y;
    std::vector<int> found_instructors_x;
    std::vector<int> found_instructors_y;

    for (int person = 0; person < this->n_people; person++)
    {
        int dest_row = 0, dest_col = 0;
        MazePerson * curr_person = this->people[person];
        std::string target_type = curr_person->get_type();

        // Handle different types
        if ((target_type == "Instructor" && found_instructors_x.size() < 1)
                | (target_type == "IntrepidStudent" && found_starts_x.size() < 1))
        {
            for (int row = 0; row < this->locations.size(); row++)
            {
                for (int col = 0; col < this->locations[row].size(); col++)
                {
                    MazeLocation * curr_loc = this->locations[row][col];

                    if (curr_loc->is_occupiable() == true)
                    {
                        OpenSpace * curr_open = static_cast<OpenSpace *>(curr_loc);

                        if (curr_open->get_has_start() == true)
                        {
                            if (target_type == "IntrepidStudent")
                            {
                                dest_row = row;
                                dest_col = col;
                                curr_open->set_has_player(true);
                            }
                            else
                            {
                                found_starts_x.push_back(col);
                                found_starts_y.push_back(row);
                            }
                        }
                        else if (curr_open->get_has_instructor() == true)
                        {
                            if (target_type == "Instructor")
                            {
                                dest_row = row;
                                dest_col = col;
                            }
                            else
                            {
                                found_instructors_x.push_back(col);
                                found_instructors_y.push_back(row);
                            }
                        }
                    }
                }
            }
        }
        else if (target_type == "Instructor" && found_instructors_x.size() > 0)
        {
            dest_col = found_instructors_x[0];
            dest_row = found_instructors_y[0];
            found_instructors_x.erase(found_instructors_x.begin());
            found_instructors_y.erase(found_instructors_y.begin());
        }
        else if (target_type == "IntrepidStudent" && found_starts_x.size() > 0)
        {
            dest_col = found_starts_x[0];
            dest_row = found_starts_y[0];

            OpenSpace * o = static_cast<OpenSpace *>(
                                this->locations[dest_row][dest_col]);
            o->set_has_player(true);

            found_starts_x.erase(found_starts_x.begin());
            found_starts_y.erase(found_starts_y.begin());
        }
        else if (target_type == "TA")
        {
            int max_tries = 50;

            for (int i = 0; i < max_tries; i++)
            {
                int rand_x = rand() % this->maze_width;
                int rand_y = rand() % this->maze_height;

                MazeLocation * rand_loc = this->locations[rand_y][rand_x];

                if (rand_loc->is_occupiable() == true)
                {
                    OpenSpace * rand_open = static_cast<OpenSpace *>(rand_loc);

                    if (rand_open->get_has_start() == false
                            && rand_open->get_has_ta() == false
                            && rand_open->get_has_instructor() == false
                            && rand_open->get_has_end() == false
                            && rand_open->get_has_p_skill() == false)
                    {
                        int safe_radius = 3;

                        bool invalid = check_intersection(rand_x, rand_y,
                                                          "IntrepidStudent",
                                                          safe_radius, true);

                        if (invalid == false)
                        {
                            /* Making sure they are away from start */
                            dest_row = rand_y;
                            dest_col = rand_x;
                            rand_open->set_has_ta(true);
                            break;
                        }
                    }
                }
            }
        }

        // Move them
        curr_person->move_to(dest_col, dest_row);
    }

    // Place p_skills
    int num_skills = 3;

    for (int i = 0; i < num_skills; i++)
    {
        int max_tries = 50;

        for (int i = 0; i < max_tries; i++)
        {
            int rand_x = rand() % this->maze_width;
            int rand_y = rand() % this->maze_height;

            MazeLocation * rand_loc = this->locations[rand_y][rand_x];

            if (rand_loc->is_occupiable() == true)
            {
                OpenSpace * rand_open = static_cast<OpenSpace *>(rand_loc);

                if (rand_open->get_has_start() == false
                        && rand_open->get_has_ta() == false
                        && rand_open->get_has_instructor() == false
                        && rand_open->get_has_end() == false
                        && rand_open->get_has_p_skill() == false)
                {
                    rand_open->set_has_p_skill(true);
                    break;
                }
            }
        }
    }
}


/*
 * Pre-condition:   the passed integers point to an OpenSpace
 * Post-condition:  the passed referenced OpenSpace has had the booleans of its contents
 *		    updated according to the people in it
 */
void MazeLevel::update_bools(int loc_x, int loc_y)
{
    if (this->locations[loc_y][loc_x]->is_occupiable() == true)
    {
        OpenSpace * curr_loc = static_cast<OpenSpace *>(this->locations[loc_y][loc_x]);

        // Clear what you have
        curr_loc->reset_moving_contents();

        // Set accurate vals
        for (int i = 0; i < this->n_people; i++)
        {
            if (this->people[i]->get_x_pos() == loc_x
                    && this->people[i]->get_y_pos() == loc_y)
            {
                if (this->people[i]->get_type() == "TA")
                {
                    curr_loc->set_has_ta(true);
                }
                else if (this->people[i]->get_type() == "IntrepidStudent")
                {
                    curr_loc->set_has_player(true);
                }
            }
        }
    }
}


/*
 * Checks for intersection of two specified types of MazePerson in a passed radius,
 *  including corners (so it'll be a variably large square rather than bad circle).
 */
bool MazeLevel::check_intersection(std::string type_a,
                                   std::string type_b,
                                   int r, bool corners)
{
    for (int i = 0; i < this->n_people; i++)
    {
        std::string curr_type = this->people[i]->get_type();

        if (curr_type == type_a || curr_type == type_b)
        {
            std::string target = (curr_type == type_a) ? (type_b) : (type_a);

            for (int j = i; j < this->n_people; j++)
            {
                if (this->people[j]->get_type() == target)
                {
                    MazePerson * person_a = this->people[i];
                    MazePerson * person_b = this->people[j];

                    if ((abs(person_a->get_x_pos() - person_b->get_x_pos()) <= r)
                            && (abs(person_a->get_y_pos() - person_b->get_y_pos()) <= r))
                    {
                        if (corners == true)
                        {
                            return true;
                        }
                        else
                        {
                            if (person_a->get_x_pos() == person_b->get_x_pos()
                                    || person_a->get_y_pos() == person_b->get_y_pos())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }

        std::cout << std::endl;
    }

    return false;
}


/*
 * Checks for intersection of a specified type of MazePerson in a passed radius,
 *  including corners, of a passed position in the level.
 */
bool MazeLevel::check_intersection(int x, int y,
                                   std::string type,
                                   int r, bool corners)
{
    for (int i = 0; i < this->n_people; i++)
    {
        if (this->people[i]->get_type() == type)
        {
            MazePerson * p = this->people[i];

            if (abs(p->get_x_pos() - x) <= r && abs(p->get_y_pos() - y) <= r)
            {
                if (corners == true)
                {
                    return true;
                }
                else
                {
                    if (p->get_x_pos() == x || p->get_y_pos() == y)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
