#include "Matrix.hpp"
#include "SizeMismatch.hpp"
#include <iostream>
#include <cmath>

int main()
{
    /* Create Matrices */
    Matrix<int> i_mat(4, 4);
    Matrix<int> f_mat(4, 4);
    Matrix<float> w_mat(6, 6);
    Matrix<int> s_mat(1, 1);


    std::cout << std::endl;
    std::cout << "i_mat is Matrix of ints with (4,4)   - multiplication table" << std::endl;
    std::cout << "f_mat is Matrix of ints with (4,4)   - power table" << std::endl;
    std::cout << "w_mat is Matrix of floats with (6,6) - division table" << std::endl;
    std::cout << "s_mat is Matrix of ints with (1,1)   - just 6609" << std::endl;
    std::cout << std::endl;


    /* Fill the Matrices */
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            i_mat.at(i, j) = i * j;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            f_mat.at(i, j) = std::pow(i, j);
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            w_mat.at(i, j) = float(i) / j;
        }
    }

    s_mat.at(0, 0) = 6609;


    /* Try to access out of bounds */
    std::cout << "TRYING TO ACCESS (0,2) IN S_MAT." << std::endl;

    try
    {
        s_mat.at(0, 1) = 2;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }


    /* Print the Matrices */
    std::cout << std::endl;
    std::cout << "i_mat.print():" << std::endl;
    i_mat.print();
    std::cout << std::endl << "f_mat.print():" << std::endl;
    f_mat.print();
    std::cout << std::endl << "w_mat.print():" << std::endl;
    w_mat.print();
    std::cout << std::endl << "s_mat.print():" << std::endl;
    s_mat.print();
    std::cout << std::endl;


    /* Try to add mismatch sizes */
    std::cout << "TRYING TO ADD I_MAT to S_MAT" << std::endl;

    try
    {
        s_mat.add(i_mat);
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;

    }


    /* Reprint the Matrices */
    std::cout << std::endl;
    std::cout << "i_mat.print():" << std::endl;
    i_mat.print();
    std::cout << std::endl << "f_mat.print():" << std::endl;
    f_mat.print();
    std::cout << std::endl << "w_mat.print():" << std::endl;
    w_mat.print();
    std::cout << std::endl << "s_mat.print():" << std::endl;
    s_mat.print();
    std::cout << std::endl;


    /* Return */
    return 0;
}
