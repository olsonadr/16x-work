Week 6 Lab Exercise
===================

This is the repo for CS 162's Lab #6.  You will commit your source code files into this repository for the TAs to check off.  The description of the lab exercise is below and can also be found here:

https://docs.google.com/document/d/1inAoXBmmONesrI0LrJSnh4lDPeRqtny27iA8cd8vg_o/edit?usp=sharing

In this lab, you’ll start to work with inheritance in C++.

## Step 1: Clone the git repository for this lab

We’re going to use git and GitHub Classroom again for this lab.  Just like you did for the previous lab exercises, use git clone to download your repository onto your development machine using the clone URL from your repo on GitHub:
```
git clone REPO_URL
```

## Step 2: Implement a generic `Shape` class

We’re going to work with shapes in this lab exercise.  We’ll create several classes to represent different shapes, some of them using inheritance. The first class we’ll write is one to represent a generic shape with a name and a color.

Create two new files, `shape.hpp` and `shape.cpp`, and in them, define a `Shape` class.  Here’s the start of a class definition you should use:

```c++
class Shape {
private:
  std::string name;
s td::string color;
public:
  ...
};
```

You class should also have constructors, accessors, and mutators, as appropriate.  In addition, your class should have an `area()` method for computing the shape’s area.  For this generic `Shape` class, the `area()` method can simply return 0, since we aren’t actually defining the shape itself.

In addition to your files `shape.hpp` and `shape.cpp`, create a new file `application.cpp`.  In this file, write a simple `main()` function that instantiates some `Shape` objects and prints out their information.  In addition, write a `Makefile` to specify compilation of your program.  Make sure you compile your `Shape` class into an object file first, separately from the compilation of your application, and then use that object file when you’re compiling your application.

Once you have this all working, commit your `shape.hpp`, `shape.cpp`, `application.cpp`, and `Makefile` into your git repository, and push them back to your remote repo on GitHub.

## Step 3: Implement `Rectangle` and `Circle` classes

Create new files `rectangle.hpp`, `rectangle.cpp`, `circle.hpp`, and `circle.cpp`, and in them, implement a `Rectangle` class and a `Circle` class.  Both of these classes should be derived from your `Shape` class.  The `Rectangle` class should have a `width` and a `height`, and the `Circle` class should have a `radius`.  Here are the beginnings of definitions for these classes:

```c++
class Rectangle : public Shape {
private:
  float width;
  float height;
public:
  ...
};

class Circle : public Shape {
private:
  float radius;
public:
  ...
};
```

Both of these classes should have constructors, accessors, and mutators, as needed, and each one should override the `Shape` class’s `area()` method to compute areas that are appropriate for rectangles and circles.

Add some code to your application to instantiate and print out some `Rectangle` and `Circle` objects, and add rules to your `Makefile` to compile each of your new classes into separate object files, which you should then use when compiling your application.

Once you have this all working, add your new files to your git repository, commit all of your changes, and push them to your remote repo on GitHub.

## Step 4: Implement a Square class

Now, create new files `square.hpp` and `square.cpp`, and in them, implement a `Square` class that derives from your `Rectangle` class.  Your `Square` class *should not* contain any new data members, nor may you change any members of the `Rectangle` class to `protected` or `public` access.  Instead, you should figure out how to implement a public interface for your `Square` class by appropriately using the `width` and `height` of your Rectangle class via its public interface (i.e. via the `Rectangle` class’s constructors, accessors, and mutators).  Specifically, the public interface to your `Square` class should use the public interface of your `Rectangle` class while enforcing the constraint that a square’s width and height are equal.

Here’s the start of a definition for your `Square` class, with no new data members:

```c++
class Square : public Rectangle {
public:
  ...
};
```

Once your `Square` class is written, add some lines to your application to instantiate and print out some `Square` objects, and add a `Makefile` rule to compile your class into an object file that’s used in the compilation of your application.  Make sure to add your new files to your git repo, commit all of your changes, and push them to your remote repo on GitHub.

## Grading Criteria

That’s it!  After you’re done with your lab, make sure you get it checked off by your TA so that you get points for it.  If you don’t get your work checked off, you’ll receive a zero for the lab, and we won’t be able to change your grade, since we’ll have no way to know whether or not you were at the lab.

This lab is worth 10 points total.  Here’s the breakdown:
  * 4 points: `Shape` class, application, and makefile (i.e. done through Step 2)
  * 4 points: `Rectangle` and `Circle` classes (i.e. done through Step 3)
  * 2 points: `Square` class (i.e. done through Step 4)
