#include "geometries/Geometry.hpp"

#ifndef PLANE_HPP
#define PLANE_HPP

namespace t {

/**
  v1--v0
  |\  |    +Y
  | \ |     |
  |  \|     |---+X
  v2--v3
*/

#define halfWidth width / 2
#define halfHeight height / 2

#define vertexBuffer                                                           \
  {                                                                            \
      halfWidth,  halfHeight,  0, /* v0 */                                     \
      -halfWidth, halfHeight,  0, /* v1 */                                     \
      -halfWidth, -halfHeight, 0, /* v2 */                                     \
      halfWidth,  -halfHeight, 0, /* v3 */                                     \
  }

#define indexBuffer {0, 1, 3, 3, 1, 2}
#define normalBuffer {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}

class Plane : public Geometry {
public:
  Plane(double width, double height)
      : Geometry(BufferAttribute<double>(vertexBuffer, 3),
                 BufferAttribute<double>(normalBuffer, 3)) {
    setIndices(BufferAttribute<int>(indexBuffer, 3));
  }
};

#undef vertexBuffer
#undef indexBuffer
#undef normalBuffer
#undef halfWidth
#undef halfHeight

} // namespace t

#endif // PLANE_HPP