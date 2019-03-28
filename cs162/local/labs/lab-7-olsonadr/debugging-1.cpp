/*
 * This program should compute do some simple setting and printing of values.
 *
 * Once compiled, you can run this program like so:
 *   ./debugging-1
 */

#include <iostream>

void setval(int * i_ptr, int val)
{
    *i_ptr = val;
}

int main(int argc, char ** argv)
{
    int a;
    setval(&a, 13);
    std::cout << "a: " << a << std::endl;

    int * b = new int;
    setval(b, 4);
    std::cout << "*b:" << *b << std::endl;

    delete b;
}
