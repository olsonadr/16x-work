/*
 * This file contains member functiond definitions for the Dynarray class.
 */

#include <iostream>

#include "dynarray.hpp"

#define INIT_CAPACITY 16

Dynarray::Dynarray() {
  this->data = new int[INIT_CAPACITY];
  this->n = 0;
  this->capacity = INIT_CAPACITY;
}

Dynarray::Dynarray(const Dynarray &old_d)
{
    this->data = new int[old_d.capacity];
    this->n = old_d.n;
    this->capacity = old_d.capacity;

    for(int i = 0; i < this->n; i++)
    {
	this->data[i] = old_d.data[i];
    }
}

void Dynarray::operator=(const Dynarray &old_d)
{
    delete[] this->data;
    this->data = new int[old_d.capacity];
    this->n = old_d.n;
    this->capacity = old_d.capacity;

    for(int i = 0; i < this->n; i++)
    {
	this->data[i] = old_d.data[i];
    }
}

Dynarray::~Dynarray() {
  delete[] this->data;
}

/*
 * Returns the number of elements stored in the array.
 */
int Dynarray::size() {
  return this->n;
}

/*
 * Adds a new value to the end of the array.
 */
void Dynarray::add(int v) {
  /*
   * If we don't have enough space in the current array to add another item,
   * then double the size of the array by creating a new array and copying the
   * old data over to it.
   */
  if (this->n == this->capacity) {
    int new_capacity = 2 * this->capacity;
    int* new_data = new int[new_capacity];
    for (int i = 0; i < this->n; i++) {
      new_data[i] = this->data[i];
    }
    delete[] this->data;
    this->data = new_data;
    this->capacity = new_capacity;
  }

  this->data[this->n++] = v;
}

/*
 * Returns the array value stored at a specified index.  Does not error check
 * the index, so you need to make sure it's within the bounds of the array
 * before calling this function.
 */
int Dynarray::get(int i) {
  return this->data[i];
}
