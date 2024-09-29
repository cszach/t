#include "math/Vector3.hpp"

#ifndef VARYINGS_HPP
#define VARYINGS_HPP

namespace t {

/**
 * The varyings available to {@linkplain Material#fragmentShader fragment
 * shaders}.
 *
 * Varyings are values that are interpolated between fragments in a single draw
 * call.
 *
 * @see Fragment
 *
 * \ingroup primitives
 */
struct Varyings {
  Vector3 &localPosition; /**< The position in local space associateed with the
                             current fragment. */
  Vector3 &localNormal;   /**< The normal vector in local space associated with
                             the current fragment. */
};

} // namespace t

#endif // VARYINGS_HPP