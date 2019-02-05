/*
 *  The Container class, which describes its children Window and
 *  Panel, which both contain other elements within them.
 */

#include "../headers/Container.hpp"

// Protected
void Container::grow_members()
{
    Element *temp_members[this->n_members];
    for (int i = 0; i < this->n_members; i++)
    {
        temp_members[i] = this->members[i];
    }
    delete[] this->members;

    this->len_members *= 2;
    this->members = new Element *[this->len_members * 2];

    for (int i = 0; i < this->n_members; i++)
    {
        this->members[i] = temp_members[i];
    }
}

void Container::reset_merged()
{
    for (int row = 0; row < this->dim.y; row++)
    {
        for (int col = 0; col < this->dim.x; col++)
        {
            this->merged_arr[row][col] = ' ';
        }
    }
}

// Public
void Container::add(Element passed_element)
{
    while (this->n_members >= this->len_members)
    { /* The members arr is at capacity */
        grow_members();
    }

    this->members[n_members] = new Element(passed_element);
    this->n_members++;
    this->has_changed = true;
}

void Container::remove(int index)
{
    for (int i = index + 1; i < this->n_members; i++)
    {
        this->members[i - 1] = this->members[i];
    }

    this->members[n_members - 1] = nullptr;
    this->n_members--;
    this->has_changed = true;
}

char **Container::merge()
{
    bool must_update = this->has_changed;
    if (must_update == false)
    {
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->has_changed())
            {
                must_update = true;
            }
        }
    }

    if (must_update)
    {
        reset_merged();
        for (int i = 0; i < this->n_members; i++)
        {
            if (this->members[i]->get_is_visible())
            { /* Member is visible, will be layered onto container's output */

                if (this->members[i]->get_type() == "Label")
                { /* Member is a Label */

                    Label *curr_member =
                        static_cast<Label *>(this->members[i]);

                    int row = curr_member->get_pos().y;
                    int col = curr_member->get_pos().x;

                    for (int j = 0; j < curr_member->get_len(); j++)
                    {
                        // Check for \n escape character
                        if (curr_member->get_str()[j] == '\\' &&
                            j + 1 < curr_member->get_len() &&
                            curr_member->get_str()[j + 1] == 'n')
                        { /* Line-break (\n) at current j */
                            j++;
                            row++;
                            if (!curr_member->get_is_vertical())
                            { /* Label is horizontal (on \n reset to left) */
                                col = curr_member->get_pos().x;
                            }
                            continue;
                        }

                        // Set position in merged arr if in bounds
                        if (row < this->dim.y &&
                            col < this->dim.x)
                        {
                            this->merged_arr[row][col] = curr_member->get_str()[j];
                        }

                        // Move cursor to next position for Label
                        if (curr_member->get_is_vertical())
                        {
                            row++;
                        }
                        else
                        {
                            col++;
                        }
                    }
                }

                else if (this->members[i]->get_type() == "Panel")
                { /* Member is a Panel */

                    Container *curr_member =
                        static_cast<Container *>(this->members[i]);

                    int row;
                    int col;

                    // Merge the panel and store its result
                    char **curr_member_contents = curr_member->merge();

                    for (int m_row = 0; m_row < curr_member->get_dim().y; m_row++)
                    { /* For each row in curr_member */

                        row = curr_member->get_pos().y + m_row;

                        for (int m_col = 0; m_col < curr_member->get_dim().x; m_col++)
                        { /* For each column in curr_member */

                            col = curr_member->get_pos().x + m_col;
                            // Set position in merged arr if in bounds
                            if (row < this->dim.y &&
                                col < this->dim.x)
                            {
                                this->merged_arr[row][col] = curr_member_contents[m_row][m_col];
                            }
                        }
                    }
                }
            }
        }
    }

    return this->merged_arr;
}