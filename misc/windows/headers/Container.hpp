/*
 *  The Container class, which describes its children Window and
 *  Panel, which both contain other elements within them.
 */

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Element.hpp"
#include "Label.hpp"

class Container : public Element
{
protected:
  // Fields (inherits visibility, type, position)
  struct int_duple dim; /* Dimensions of the container */
  char **merged_arr;    /* Dynamic 2D arr of chars of merged layers */
  Element **members;    /* Dynamic array of Element pointers */
  int n_members;        /* Number of members in members arr */
  int len_members;      /* Lenfth of members arr */

  // Methods
  void grow_members(); /* Increases size of members array */
  void reset_merged(); /* Resets the merged arr to blank (has_changed) */

public:
  // Accessors
  int_duple get_dim() { return this->dim; }
  int get_n_members() { return this->n_members; }
  Element *get_member(int index) { return this->members[index]; }

  // Mutators
  void add(Element passed_element);
  void remove(int index);
  char **merge();
};

#endif