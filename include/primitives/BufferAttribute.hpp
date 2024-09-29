#include <initializer_list>
#include <span>
#include <vector>

#ifndef BUFFERATTRIBUTE_HPP
#define BUFFERATTRIBUTE_HPP

namespace t {

/**
 * A class representing attributes, such as vertex positions, face indices, and
 * vertex normals.
 *
 * An attribute is a buffer (array) storing data associated with a type of
 * primitve. For example:
 * - the vertex positions attribute (a.k.a. the vertex buffer) stores the
 * positions of the vertices of a mesh. Every 3 consecutive values in the array
 * specify the x, y, and z coordinates of a vertex. It is required for all
 * {@linkplain Geometry geometries};
 * - the face indices attribute (a.k.a. the index buffer) stores the indices of
 * the vertices of the faces of a mesh;
 * - the vertex normals attribute (a.k.a. the normal buffer) stores the vertex
 * normals of a mesh.
 *
 * \ingroup primitives
 */
template <class BufferType> class BufferAttribute {
public:
  std::vector<BufferType>
      array;    /**< The array holding the data of the attribute. */
  int itemSize; /**< The number of values of the array that are associated with
                   a particular vertex e.g. for vertex positions, `itemSize`
                   should be 3 as a position in 3D space is specified using 3
                   values. */

  /**
   * Creates a new buffer attribute with the specified array and item size.
   *
   * @param _array The array holding the data of the attribute.
   * @param _itemSize The number of values of the array that are associated with
   * a particular vertex.
   */
  BufferAttribute(std::initializer_list<BufferType> _array, int _itemSize)
      : array(_array), itemSize(_itemSize) {}
};

} // namespace t

#endif // BUFFERATTRIBUTE_HPP