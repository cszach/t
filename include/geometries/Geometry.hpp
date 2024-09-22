#include "primitives/BufferAttribute.hpp"
#include <memory>
#include <optional>

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace t {

class Geometry {
public:
  BufferAttribute<double> vertexPositions;
  std::optional<BufferAttribute<int>> faceIndices;
  BufferAttribute<double> vertexNormals;
  FrontFace frontFace = FrontFace::CounterClockwise;

  Geometry(const BufferAttribute<double> &_vertexPositions,
           const BufferAttribute<double> &_vertexNormals)
      : vertexPositions(_vertexPositions), vertexNormals(_vertexNormals) {}

  void setIndices(BufferAttribute<int> indices) { faceIndices = indices; }
};

} // namespace t

#endif // GEOMETRY_HPP