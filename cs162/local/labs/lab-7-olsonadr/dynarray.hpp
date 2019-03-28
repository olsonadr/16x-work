/*
 * This file contains the definition of a simple class representing a dynamic
 * array of integers (i.e. an array of integers that grows as needed).
 */

#ifndef __DYNARRAY_HPP
#define __DYNARRAY_HPP

class Dynarray {
private:
  int* data;
  int n;
  int capacity;
public:
  Dynarray();
  Dynarray(const Dynarray &old_d);
  void operator=(const Dynarray &old_d);
  ~Dynarray();
  int size();
  void add(int v);
  int get(int i);
};

#endif
