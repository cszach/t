#include "geometries/Geometry.hpp"

#ifndef BOX_HPP
#define BOX_HPP

namespace t {

//   v2-------v3
//   /|       /|
// v1-------v0 |    +Y
//  | |      | |     |
//  |v6------|v7     |---+X
//  |/       |/     /
// v5-------v4    +Z

#define halfWidth width / 2
#define halfHeight height / 2
#define halfDepth depth / 2

// clang-format off
#define vertexBuffer {                                \
   /* v0 */                                           \
   halfWidth,  halfHeight,  halfDepth, /* 0 X face */ \
   halfWidth,  halfHeight,  halfDepth, /* 1 Y face */ \
   halfWidth,  halfHeight,  halfDepth, /* 2 Z face */ \
                                                      \
   /* v1 */                                           \
  -halfWidth,  halfHeight,  halfDepth, /* 3 */        \
  -halfWidth,  halfHeight,  halfDepth, /* 4 */        \
  -halfWidth,  halfHeight,  halfDepth, /* 5 */        \
                                                      \
   /* v2 */                                           \
  -halfWidth,  halfHeight, -halfDepth, /* 6 */        \
  -halfWidth,  halfHeight, -halfDepth, /* 7 */        \
  -halfWidth,  halfHeight, -halfDepth, /* 8 */        \
                                                      \
   /* v3 */                                           \
   halfWidth,  halfHeight, -halfDepth, /* 9 */        \
   halfWidth,  halfHeight, -halfDepth, /* 10 */       \
   halfWidth,  halfHeight, -halfDepth, /* 11 */       \
                                                      \
   /* v4 */                                           \
   halfWidth, -halfHeight,  halfDepth, /* 12 */       \
   halfWidth, -halfHeight,  halfDepth, /* 13 */       \
   halfWidth, -halfHeight,  halfDepth, /* 14 */       \
                                                      \
   /* v5 */                                           \
  -halfWidth, -halfHeight,  halfDepth, /* 15 */       \
  -halfWidth, -halfHeight,  halfDepth, /* 16 */       \
  -halfWidth, -halfHeight,  halfDepth, /* 17 */       \
                                                      \
   /* v6 */                                           \
  -halfWidth, -halfHeight, -halfDepth, /* 18 */       \
  -halfWidth, -halfHeight, -halfDepth, /* 19 */       \
  -halfWidth, -halfHeight, -halfDepth, /* 20 */       \
                                                      \
   /* v7 */                                           \
   halfWidth, -halfHeight, -halfDepth, /* 21 */       \
   halfWidth, -halfHeight, -halfDepth, /* 22 */       \
   halfWidth, -halfHeight, -halfDepth, /* 23 */       \
}

#define indexBuffer {                   \
   0, 12, 21, 21,  9,  0, /* +X face */ \
   1, 10,  7,  7,  4,  1, /* +Y face */ \
   2,  5, 14, 14,  5, 17, /* +Z face */ \
   3,  6, 18, 18, 15,  3, /* -X face */ \
  16, 19, 13, 13, 19, 22, /* -Y face */ \
   8, 11, 20, 20, 11, 23, /* -Z face */ \
}

#define normalBuffer {                     \
  /*X normal| Y normal| Z normal*/         \
     1, 0, 0, 0,  1, 0, 0, 0,  1, /* v0 */ \
    -1, 0, 0, 0,  1, 0, 0, 0,  1, /* v1 */ \
    -1, 0, 0, 0,  1, 0, 0, 0, -1, /* v2 */ \
     1, 0, 0, 0,  1, 0, 0, 0, -1, /* v3 */ \
     1, 0, 0, 0, -1, 0, 0, 0,  1, /* v4 */ \
    -1, 0, 0, 0, -1, 0, 0, 0,  1, /* v5 */ \
    -1, 0, 0, 0, -1, 0, 0, 0, -1, /* v6 */ \
     1, 0, 0, 0, -1, 0, 0, 0, -1, /* v7 */ \
}
// clang-format on

class Box : public Geometry {
public:
  Box(double width, double height, double depth)
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
#undef halfDepth

} // namespace t

#endif // BOX_HPP