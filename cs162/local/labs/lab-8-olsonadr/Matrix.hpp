/*
 * Matrix template class
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <exception>
#include <iostream>

#include "SizeMismatch.hpp"

class OutOfBoundsException : public std::exception
{
    public:
        virtual const char * what() const throw()
        {
            return "Referenced data outside of Matrix bounds!";
        }
};

template <class T>
class Matrix
{
    private:
        /* Fields */
        int _rows;
        int _cols;
        T ** data;

    public:
        /* Constructor */
        Matrix(int m_rows, int m_cols)
            : _rows(m_rows), _cols(m_cols)
        {
            this->data = new T*[m_rows];

            for (int i = 0; i < m_rows; i++)
            {
                this->data[i] = new T[m_cols];
            }
        }


        /* Destructor */
        ~Matrix()
        {
            for (int i = 0; i < this->_rows; i++)
            {
                delete[] this->data[i];
            }

            delete[] data;
        }


        /* Direct Accessors */
        int get_rows() { return this->_rows; }
        int get_cols() { return this->_cols; }


        /* Data Accessor / Mutator */
        T & at(int m_row, int m_col)
        {
            if (m_row >= this->_rows ||
                    m_col >= this->_cols)
            {
                throw OutOfBoundsException();
            }
            else
            {
                return this->data[m_row][m_col];
            }
        }


        /* Printer */
        void print()
        {
            for (int row = 0; row < this->_rows; row++)
            {
                std::cout << "| ";

                for (int col = 0; col < this->_cols; col++)
                {
                    std::cout << this->data[row][col] << " | ";
                }

                std::cout << std::endl;
            }
        }


        /* Adder */
        void add(const Matrix<T> & other)
        {
            if (this->_rows != other._rows ||
                    this->_cols != other._cols)
            {
                throw SizeMismatch(this->_rows, this->_cols,
                                   other._rows, other._cols);
            }
            else
            {
                for (int row = 0; row < this->_rows; row++)
                {
                    for (int col = 0; col < this->_cols; col++)
                    {
                        this->data[row][col] += other.data[row][col];
                    }
                }
            }
        }
};

#endif
