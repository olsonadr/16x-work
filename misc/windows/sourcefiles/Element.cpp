/*
 *  Element class, which is inherited by Container and Component
 *  for some sick curses-esque rendering.
 */

#include "../headers/Element.hpp"

void Element::toggle_visible()
{
    this->is_visible = !(this->is_visible);
    this->has_changed = true;
}