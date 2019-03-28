Lab Exercise #8
===============

This is the repo for CS 162's Lab #8.  You will commit your source code files into this repository for the TAs to check off.  The description of the lab exercise can be found here:

https://docs.google.com/document/d/1xkceZkTgsAoWyzhfY_hRGswquh2m29xaSeMr4Zch5c0/edit?usp=sharing

In this lab, you’ll use both templates and exceptions to create a Matrix class that can handle multiple data types.

## Step 1: Clone the git repository for this lab

We’re going to use git and GitHub Classroom again for this lab.  Just like you did for the previous lab exercises, use git clone to download your repository onto your development machine using the clone URL from your repo on GitHub:
```
git clone REPO_URL
```

## Start a simple `Matrix` template class

In this lab, you’ll be writing a template class to represent a matrix.  Because it’s a template, your matrix class will be able to work with different types of underlying data.

Start by creating a new file `matrix.hpp`.  Inside this file, start to write your matrix template class.  Here’s a start for the class definition:

```c++
template <class T>
class Matrix {
private:
  int _rows;
  int _cols;
  T** data;
public:
  Matrix(int rows, int cols);
  ~Matrix();
  int rows();
  int cols();
  T& at(int row, int col);
};
```

Here, the constructor should allocate the `data` field so that it contains the specified number of rows and columns, and the destructor should free the memory allocated to the `data` field (in addition to anything else you need to do in the destructor).  In addition to the constructor and destructor, you should write accessors to return the number of rows and the number of columns.

You should also write an `at()` method that returns a reference to the data element at a specified location.  By returning a reference, you can use the `at()` method to set values in a matrix as well as access them.  The `at()` method should throw an [`std::out_of_range`](http://www.cplusplus.com/reference/stdexcept/out_of_range/) exception if either the specified row or the specified column is outside the bounds of the matrix.

Remember, all of the methods for a template class need to be implemented directly in the header file itself.

Once you have your `Matrix` class looking good, create a new file `application.cpp`.  In this file, write a small application to test your `Matrix` class.  Create a few `Matrix` objects containing different data types, like `int`, `float`, and `double`.  Fill those `Matrix` objects with values using loops and the `at()` method, and print out some values from the matrices to make sure they look like what you expect.  Try to access some values outside the bounds of your matrices to make sure an exception is thrown.

Make sure to add and commit your files to your git repository and push them to GitHub.

## Step 3: Implement an `add()` method to add two matrices
Add a new method `add()` to your `Matrix` template class to add two `Matrix` objects.  The declaration of this method inside your class definition should look like this:

```c++
void add(const Matrix<T>& other);
```

Importantly, note that the `Matrix` argument to your `add()` method will also be of the same type `T`.  The `add()` method should simply take the value at each location in `other` and add it to the value at the corresponding location of the `Matrix` object represented by `this`, replacing the latter with the sum of the two values.

Make sure to augment your application to test your `add()` method, commit your changes to your git repository, and push them to GitHub when everything is working.

## Step 4: Write a `size_mismatch` exception and throw it in `add()`

One major catch about adding two matrices is that they must have the same dimensions.  Otherwise, it’s not possible to add them.  Your `Matrix` class should not allow the user to pass an argument `other` to the `add()` method that has different dimensions than the `Matrix` object represented by `this`.  To do this, you should create a new file `size_mismatch.hpp` and, in it, write a new exception class called `size_mismatch`.  This class should be derived from the `std::exception` class.  Remember, at a minimum, a new class that derives from `std::exception` must implement the following method:

```c++
virtual const char* what() const throw();
```

However, you may implement any additional methods that help you make an informative exception (e.g. a new parameterized constructor).  You may also add new private data members if needed.  You may place the implementations of the class methods for `size_mismatch` directly in the class definition in `size_mismatch.hpp`, or you may create a new file `size_mismatch.cpp` in which to place these implementations.

Once you have your `size_mismatch` class written, augment your `Matrix` class’s `add()` method to throw a `size_mismatch` whenever the `other` argument has different dimensions than the `Matrix` object represented by `this`.

As always, make sure to add your new files and commit your changes to your git repository, and push them to GitHub.

## Grading Criteria

That’s it!  After you’re done with your lab, make sure you get it checked off by your TA so that you get points for it.  If you don’t get your work checked off, you’ll receive a zero for the lab, and we won’t be able to change your grade, since we’ll have no way to know whether or not you were at the lab.

This lab is worth 10 points total.  Here’s the breakdown:
  * 5 points: `Matrix` template class
  * 2 points: `add()` method (without the `size_mismatch` exception)
  * 3 points: `size_mismatch` exception written and used in `add()`
