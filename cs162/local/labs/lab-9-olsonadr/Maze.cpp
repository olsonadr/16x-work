/*
 * Maze Class Implementation
 */

#include "Maze.hpp"

Maze::Maze(const char ** m_str,
           int m_width,
           int m_height)
    : maze_width(m_width),
      maze_height(m_height)
{
    // Allocate
    this->locations.resize(m_height);

    for (int row = 0; row < m_height; row++)
    {
        this->locations[row].resize(m_width);

        for (int col = 0; col < m_width; col++)
        {
            // Fill
            char curr_char = m_str[row][col];

            if (curr_char == '#')
            {
                this->locations[row][col] = new Wall();
            }
            else
            {
                OpenSpace * new_open = new OpenSpace();

                if (curr_char == '@')
                {
                    new_open->set_has_start(true);
                    new_open->set_has_player(true);
                }
                else if (curr_char == '^')
                {
                    new_open->set_has_end(true);
                }

                this->locations[row][col] = new_open;
            }
        }
    }
}


Maze::~Maze()
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
 * Pre-condition:   m_row and m_col must be in bounds, if not, return nullptr
 */
MazeLocation * Maze::get_location(int m_row, int m_col)
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


void Maze::display_maze()
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


void Maze::display_maze_occupiable()
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


void Maze::set_init_pos(Explorer * e)
{
    for (int row = 0; row < this->maze_height; row++)
    {
        for (int col = 0; col < this->maze_width; col++)
        {
            if (this->locations[row][col]->is_occupiable() == true)
            {

                OpenSpace * curr_loc = static_cast<OpenSpace *>(this->locations[row][col]);

                if (curr_loc->get_has_start() == true)
                {
                    e->move_to(col, row);
                }
            }
        }
    }
}
