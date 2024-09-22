#include "math/Matrix4x4.hpp"
#include "primitives/Object3D.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

namespace t {

class Camera : public Object3D {
public:
  Matrix4x4 projectionMatrix;

  explicit Camera(const Matrix4x4 &projectionMatrix)
      : projectionMatrix(projectionMatrix) {}
};

} // namespace t

#endif // CAMERA_HPP