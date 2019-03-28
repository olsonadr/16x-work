/*
 * Maze Class Implementation
 */

#include "Maze.hpp"

// Constructor, etc.
Maze::Maze(std::string path_to_maze)
    : n_moves_made(0), curr_level(0)//, n_people(0)
{
    // Open and get basic stuff from file
    std::ifstream maze_file;
    maze_file.open(path_to_maze);

    if (maze_file.is_open() == false)
    {
        maze_file.open("../" + path_to_maze);

        if (maze_file.is_open() == false)
        {
            std::cout << "Path to maze = " << path_to_maze << std::endl;
            throw "Opening of maze file failed!";
        }
    }

    int m_width = -1, m_height = -1, n_levels = -1;

    try
    {
        maze_file >> n_levels
                  >> m_height
                  >> m_width;

        maze_file.ignore();
    }
    catch (...)
    {
        throw "Read error! Invalid Maze formatting!";
    }

    if (n_levels < 0 || m_height < 0 || m_width < 0)
    {
        throw "Invalid formatting in Maze file!";
    }

    // Store values
    this->maze_width = m_width;
    this->maze_height = m_height;
    this->n_levels = n_levels;
    this->rounds_appeased = 0;

    // Construct and populate levels
    this->levels = new MazeLevel*[n_levels];

    for (int i = 0; i < n_levels; i++)
    {
        this->levels[i] = new MazeLevel(maze_file, m_width, m_height);
    }

    // Cleanup
    maze_file.close();
}


Maze::~Maze()
{
    for (int i = 0; i < this->n_levels; i++)
    {
        delete this->levels[i];
    }

    delete[] this->levels;
}


// Specific functions
/*
 * Pre-conditions:  the level has had all the necessary MazePeople added to the Maze
 * Post-conditions: the level is ready for play, all MazePeople and p_skills have
 *			been placed appropriately (randomly).
 */
void Maze::level_setup()
{
    this->levels[this->curr_level]->reset_level();
}


std::vector<char> Maze::level_moves()
{
    this->n_moves_made++;
    return this->levels[this->curr_level]->get_moves();
}


void Maze::go_up_level()
{
    this->curr_level++;
}


// From MazeLevel (passing down)
void Maze::add_to(int i, MazePerson * new_person)
{
    this->levels[i]->add_person(new_person);
}


void Maze::add_to_all(MazePerson * new_person)
{
    for (int i = 0; i < this->n_levels; i++)
    {
        this->levels[i]->add_person(new_person);
    }
}


void Maze::display_level()
{
    this->levels[this->curr_level]->display_maze();
}


void Maze::display_level_ta()
{
    this->levels[this->curr_level]->display_maze_ta(this->corners_count);
}


void Maze::reset_curr_level()
{
    this->levels[this->curr_level]->reset_level();
}


bool Maze::check_intersection(std::string type_a, std::string type_b, int r, bool c)
{
    return this->levels[this->curr_level]->check_intersection(type_a, type_b, r, c);
}


bool Maze::check_intersection(int x, int y, std::string type, int r, bool c)
{
    return this->levels[this->curr_level]->check_intersection(x, y, type, r, c);
}


/*
 * Gets a location at a passed row and column of the current level
 */
MazeLocation * Maze::get_location(int m_row, int m_col)
{
    return this->levels[this->curr_level]->get_location(m_row, m_col);
}
