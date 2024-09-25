#include "primitives/BufferAttribute.hpp"
#include <memory>
#include <optional>

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace t {

/**
 * A base class for 3D geometries. A 3D geometry defines the shape of a 3D
 * object.
 *
 * A 3D geometry is defined in terms of triangles (which have 3 vertices each)
 * and contains the following data:
 * - Vertex positions (**required**): the positions of the geometry's vertices,
 *   relative to its origin (or center);
 * - Vertex normals (**required**): the normal vectors of the geometry's
 *   vertices, which are vectors pointing at the direction the corresponding
 *   vertex is facing. Used for lighting calculations;
 * - Face indices (**optional**): the indices of the vertices that make up the
 *   triangles. If this data is missing, then it is assumed that every 3
 *   consecutive vertices in the vertex position buffer form a triangle.
 *
 * Here is an example of creating a simple depth-less triangle geometry.
```cpp
auto vertexPositions = BufferAttribute<double>({0, 1, 0, -1, 0, 0, 1, 0, 0}, 3);
auto vertexNormals = BufferAttribute<double>({0, 0, 1, 0, 0, 1, 0, 0, 1}, 3);

auto triangleGeometry = Geometry(vertexPositions, vertexNormals);
```
 * In the above example, the triangle has 3 vertices at \f$(0, 1, 0), (-1, 0,
0), (1, 0, 0)\f$. All 3 vertex normals point towards the positive Z direction
 * on creation.
 */
class Geometry {
public:
  BufferAttribute<double>
      vertexPositions; /**< The vertex buffer. Every 3 consecutive numbers in
                          this buffer define the X, Y, and Z coordinates of a
                          single vertex. The order in which a vertex appears in
                          the buffer defines its index e.g. the first 3 numbers
                          are the position of the vertex at index 0, the next 3
                          numbers are the position of the vertex at index 1, and
                          so on. If the index buffer is missing, then every 3
                          consecutive vertices (i.e. 9 consecutive numbers) in
                          this buffer form a triangle. */
  std::optional<BufferAttribute<int>>
      faceIndices; /**< The index buffer, which is optional. Every 3 consecutive
                      numbers in this buffer are the indices of the 3 vertices
                      that make up a single triangle. */
  BufferAttribute<double>
      vertexNormals; /**< The normal buffer. Every 3 consecutive numbers in this
                        buffer are the X, Y, and Z components of the normal
                        vector of the corresponding vertex. */
  FrontFace frontFace =
      FrontFace::CounterClockwise; /**< The vertex winding order which
                                      classifies the front face of a triangle.
                                      If the verticies of a triangle after
                                      having been transformed in the {@link
                                      Material#vertexShader} are in this order,
                                      then the triangle is considered to be
                                      front-facing. Used in conjunction with
                                      {@link Material#cullMode} to determine if
                                      a triangle should be drawn or not. */

  /**
   * Creates a new 3D geometry with the specified vertex buffer and normal
   * buffer.
   *
   * The new geometry will not have an index buffer by default. To set the index
   * buffer, use {@link #setIndices}.
   *
   * The new geometry will assume that the vertices for a front-facing triangle
   * appear in counter-clockwise order. See {@link #frontFace}.
   *
   * @param _vertexPositions The vertex buffer of the new geometry.
   * @param _vertexNormals The normal buffer of the new geometry.
   */
  Geometry(const BufferAttribute<double> &_vertexPositions,
           const BufferAttribute<double> &_vertexNormals)
      : vertexPositions(_vertexPositions), vertexNormals(_vertexNormals) {}

  /**
   * Sets the index buffer of this geometry.
   *
   * Every 3 consecutive numbers in this buffer are indices of vertices that
   * form a single triangle.
   *
   * @param faceIndices The new index buffer of this geometry.
   */
  void setIndices(BufferAttribute<int> _faceIndices) {
    faceIndices = _faceIndices;
  }
};

} // namespace t

#endif // GEOMETRY_HPP