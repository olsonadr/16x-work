/*
 *  Element class, which is inherited by Container and Component
 *  for some sick curses-esque rendering.
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

class Element
{
protected:
  struct int_duple
  {
    int x;
    int y;
  };
  struct int_duple pos;
  bool has_changed;
  bool is_visible;
  char *type;

public:
  int_duple get_pos() { return this->pos; }
  bool get_is_visible() { return this->is_visible; }
  bool has_changed() { return this->has_changed; }
  bool reset_has_changed() { this->has_changed = false; }
  char *get_type() { return this->type; }
  void toggle_visible();
};

#endif