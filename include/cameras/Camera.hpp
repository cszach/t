#include "math/Matrix4x4.hpp"
#include "primitives/Object3D.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

namespace t {

/**
 * The base camera class.
 *
 * A camera is simply defined in terms of its projection matrix, which will be
 * used in the render pipeline to transform the view-space coordinates into
 * normalized device coordinates (NDC).
 *
 * ### A note on normalized device coordinates
 *
 * The normalized device coordinates range from \f$(-1, -1, -1)\f$ to
 * \f$(1, 1, 1)\f$, and the bottom left corner is \f$(-1, -1, z)\f$. By default,
 * the {@link Rasterizer} use the less-than-or-equal-to comparison when
 * performing the depth test. This implies that higher Z values are further away
 * from the camera.
 *
 * \ingroup cameras
 */
class Camera : public Object3D {
public:
  Matrix4x4 projectionMatrix; /**< The projection matrix of this camera. The
                                 {@link Rasterizer} will assume that vertices
                                 transformed by this matrix will be in
                                 normalized device coordinates. */

  /**
   * Creates a new camera instance with the specified projection matrix.
   *
   * @param projectionMatrix The projection matrix of the new camera. After
   * being transformed by this matrix, the vertex should be in normalized device
   * coordinates.
   */
  explicit Camera(const Matrix4x4 &projectionMatrix)
      : projectionMatrix(projectionMatrix) {}
};

} // namespace t

#endif // CAMERA_HPP