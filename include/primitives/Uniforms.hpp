#include "math/Matrix3x3.hpp"
#include "math/Matrix4x4.hpp"
#include "math/Vector3.hpp"

#ifndef UNIFORMS_HPP
#define UNIFORMS_HPP

namespace t {

struct Uniforms {
  Matrix4x4 &modelMatrix;
  Matrix4x4 &modelViewMatrix;
  Matrix4x4 &projectionMatrix;
  Matrix4x4 &viewMatrix;
  Matrix3x3 &normalMatrix;
  Vector3 &cameraPosition;
};

} // namespace t

#endif // UNIFORMS_HPP