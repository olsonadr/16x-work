/*
 * SizeMismatch exception class header file
 */

#ifndef SIZE_MISMATCH_HPP
#define SIZE_MISMATCH_HPP

#include <cstdlib>

class SizeMismatch : public std::exception
{
    private:
        int first_row, first_col;
        int second_row, second_col;
        const char * special_str;
        bool paramaterized;

    public:
        /* Default Constructor */
        SizeMismatch() : paramaterized(false) {}


        /* Special Constructor */
        SizeMismatch(int first_row, int first_col,
                     int second_row, int second_col)
            : first_row(first_row), first_col(first_col),
              second_row(second_row), second_col(second_col),
              paramaterized(true)
        {
            char * buff = new char[200];

            sprintf(buff,
                    "The sizes of %d x %d and %d x %d do not match!\0",
                    this->first_row, this->first_col,
                    this->second_row, this->second_col);

	    this->special_str = buff;
        }


        /* Destructor */
        ~SizeMismatch()
        {
            delete this->special_str;
        }


        /* What */
        virtual const char * what() const throw()
        {
            if (this->paramaterized == true)
            {
                return this->special_str;
            }
            else
            {
                return "The two matrices have mismatching sizes!";
            }
        }
};

#endif
