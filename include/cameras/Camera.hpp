#include "math/Matrix4x4.hpp"
#include "primitives/Object3D.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

namespace t {

/**
 * The base camera class.
 *
 * A camera is simply an object that has a projection matrix, which will be used
 * in the render pipeline to transform the view coordinates into normalize
 * device coordinates (NDC).
 */
class Camera : public Object3D {
public:
  Matrix4x4 projectionMatrix; /**< The projection matrix of this camera. */

  /**
   * Creates a new camera instance with the specified projection matrix.
   */
  explicit Camera(const Matrix4x4 &projectionMatrix)
      : projectionMatrix(projectionMatrix) {}
};

} // namespace t

#endif // CAMERA_HPP