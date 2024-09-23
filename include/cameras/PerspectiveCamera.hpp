#include "cameras/Camera.hpp"
#include <cmath>

#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

namespace t {

/**
 * A camera that uses [perspective
 * projection](https://en.wikipedia.org/wiki/Perspective_(graphical)).
 *
 * The perspective camera is technically a pinhole camera and is closer to what
 * the human eye and cameras see compared to the orthographic camera. It is the
 * common choice for rendering a 3D scene.
 */
class PerspectiveCamera : public Camera {
public:
  double verticalFov; /**< The vertical field-of-view, in radians. */
  double aspectRatio; /**< The aspect ratio of this camera. */
  double near;        /**< The near plane of the view frustum. */
  double far;         /**< The far plane of the view frustum. */

  /**
   * Creates a new perspective camera.
   */
  PerspectiveCamera(
      double _verticalFov /**< [in] The vertical field-of-view,
                             _in radians_, for the new camera. */
      ,
      double _aspectRatio /**< [in] The aspect ratio of the new camera, usually
                             set to image width divided by image height. */
      ,
      double _near /**< [in] The near plane of the view frustum. Objects closer than
                      this to the camera will not be rendererd. */
      ,
      double _far /**< [in] The far plane of the view frustum. Objects further than this to the camera will not be rendered. */)
      : Camera(Matrix4x4(1.0 / (_aspectRatio * std::tan(_verticalFov / 2.0)), 0,
                         0, 0, 0, 1.0 / std::tan(_verticalFov / 2), 0, 0, 0, 0,
                         -(_far + _near) / (_far - _near),
                         (-2.0 * _far * _near) / (_far - _near), 0, 0, -1, 0)),
        verticalFov(_verticalFov), aspectRatio(_aspectRatio), near(_near),
        far(_far) {}
};

} // namespace t

#endif // PERSPECTIVECAMERA_HPP