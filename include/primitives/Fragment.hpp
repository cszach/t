#include "primitives/Color.hpp"

#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

namespace t {

/**
 * The fragment class.
 *
 * A fragment contains data generated during the rasterization process for each
 * pixel that a primitive (e.g. triangle) covers.
 *
 * \ingroup primitives
 */
struct Fragment {
  int x; /**< The x coordinate of the fragment in screen space. */
  int y; /**< The y coordinate of the fragment in screen space. */

  /**
   * The less-than comparison for fragments, used for ordered sets in
   * {@link Rasterizer} to sort fragments by their x coordinates.
   */
  bool operator<(const Fragment &b) const { return this->x < b.x; }
};

} // namespace t

#endif // FRAGMENT_HPP