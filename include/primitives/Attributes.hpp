#include "math/Vector3.hpp"

#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

namespace t {

/**
 * The attributes of a vertex, available to {@linkplain Material#vertexShader
 * vertex shaders}.
 */
struct Attributes {
  Vector3 &localPosition; /**< The local position of the current vertex. */
  Vector3 &localNormal;   /**< The local normal vector of the current vertex. */
  // uv?
};

} // namespace t

#endif // ATTRIBUTES_HPP