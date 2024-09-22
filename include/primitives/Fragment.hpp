#include "primitives/Color.hpp"

#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

namespace t {

struct Fragment {
  int x;
  int y;

  bool operator<(const Fragment &b) const { return this->x < b.x; }
};

} // namespace t

#endif // FRAGMENT_HPP