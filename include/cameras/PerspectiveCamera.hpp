#define _USE_MATH_DEFINES
#include "cameras/Camera.hpp"
#include <cmath>

#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

namespace t {

/**
 * The [perspective
 * projection](https://en.wikipedia.org/wiki/Perspective_(graphical)) camera.
 *
 * The perspective camera is technically a pinhole camera and is closer to what
 * the human eye and cameras see compared to the orthographic camera. It is the
 * common choice for rendering a 3D scene.
 *
 * A typical perspective camera instantiation might look like the following:
 * ```cpp
 * auto camera = PerspectiveCamera(M_PI / 4, width / height, 0.01, 2000);
 * ```
 * …where `width` and `height` are the output image's width and height.
 *
 * The perspective camera will use the following {@linkplain
 * Camera#projectionMatrix projection matrix}:
 * \f[
 *   \begin{bmatrix}
 *     \frac{1}{a \cdot \tan(v / 2)} & 0 & 0 & 0 \\
 *     0 & \frac{1}{\tan(v / 2)} & 0 & 0 \\
 *     0 & 0 & -\frac{f + n}{f - n} & \frac{-2 \cdot f \cdot n}{f - n} \\ 0 & 0
 * & -1 & 0 \end{bmatrix} \f]
 *
 * …where \f$a\f$, \f$v\f$, \f$f\f$, and \f$n\f$ are the aspect ratio, vertical
 * field-of-view in radians, far plane, and near plane of the camera
 * respectively and define the camera's view frustum.
 *
 * \ingroup cameras
 */
class PerspectiveCamera : public Camera {
public:
  double verticalFov; /**< The vertical field-of-view of this camera in
                         radians. */
  double aspectRatio; /**< The aspect ratio of this camera. */
  double near;        /**< The near plane of this camera's view frustum. */
  double far;         /**< The far plane of this camera's view frustum. */

  /**
   * Creates a new perspective camera.
   *
   * @param _verticalFov The vertical field-of-view, _in radians_, for the new
   * camera.
   * @param _aspectRatio The aspect ratio of the new camera, usually set to
   * image width divided by image height.
   * @param _near The near plane of the view frustum. Objects closer than this
   * to the camera will not be rendered.
   * @param _far The far plane of the view frustum. Objects further than this to
   * the camera will not be rendererd.
   */
  PerspectiveCamera(double _verticalFov, double _aspectRatio, double _near,
                    double _far)
      : Camera(Matrix4x4(1.0 / (_aspectRatio * std::tan(_verticalFov / 2.0)), 0,
                         0, 0, 0, 1.0 / std::tan(_verticalFov / 2), 0, 0, 0, 0,
                         -(_far + _near) / (_far - _near),
                         (-2.0 * _far * _near) / (_far - _near), 0, 0, -1, 0)),
        verticalFov(_verticalFov), aspectRatio(_aspectRatio), near(_near),
        far(_far) {}
};

} // namespace t

#endif // PERSPECTIVECAMERA_HPP
