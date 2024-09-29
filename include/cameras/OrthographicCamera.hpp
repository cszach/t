#include "cameras/Camera.hpp"

#ifndef ORTHOGRAPHICCAMERA_HPP
#define ORTHOGRAPHICCAMERA_HPP

namespace t {

/**
 * The [orthographic
projection](https://en.wikipedia.org/wiki/Orthographic_projection) camera.
 *
 * A typical orthographic camera instantiation might look like the following:
 *
```cpp
const auto camera = OrthographicCamera(width / -2, width / 2, height / 2, height
    / -2, 0.1, 2000 );
```
 * …where `width` and `height` are the output image's width and height.
 *
 * The orthographic camera will use the following {@linkplain
 * Camera#projectionMatrix projection matrix}:
 * \f[
 *   \begin{bmatrix}
 *     \frac{2}{r - l} & 0 & 0 & -\frac{r + l}{r - l} \\
 *     0 & \frac{2}{t - b} & 0 & -\frac{t + b}{t - b} \\
 *     0 & 0 & -\frac{2}{f - n} & -\frac{f + n}{f - n} \\
 *     0 & 0 & 0 & 1
 *   \end{bmatrix}
 * \f]
 *
 * …where \f$r\f$, \f$l\f$, \f$t\f$, \f$b\f$, \f$f\f$, \f$n\f$ are the right,
 * left, top, bottom, far, and near planes of the camera's view frustum,
 * respectively.
 *
 * \ingroup cameras
 */
class OrthographicCamera : public Camera {
public:
  double left;   /**< The left plane of this camera's view frustum. */
  double right;  /**< The right plane of this camera's view frustum. */
  double top;    /**< The top plane of this camera's view frustum. */
  double bottom; /**< The bottom plane of this camera's view frustum. */
  double near;   /**< The near plane of this camera's view frustum. */
  double far;    /**< The far plane of this camera's view frustum. */

  /**
   * Creates a new orthographic camera with the specified planes as the [view
   * frustum](https://en.wikipedia.org/wiki/Viewing_frustum).
   *
   * The view frustum of the orthographic camera is in the shape of a box. Only
   * objects in this box may appear in the render.
   *
   * The planes should be set such that `_right > _left` and `_top > _bottom`.
   *
   * @param _left The left plane of the new camera's view frustum.
   * @param _right The right plane of the new camera's view frustum.
   * @param _top The top plane of the new camera's view frustum.
   * @param _bottom The bottom plane of the new camera's view frustum.
   * @param _near The near plane of the new camera's view frustum.
   * @param _far The far plane of the new camera's view frustum.
   */
  OrthographicCamera(double _left, double _right, double _top, double _bottom,
                     double _near, double _far)
      : Camera(Matrix4x4(
            2 / (_right - _left), 0, 0, -(_right + _left) / (_right - _left), 0,
            2 / (_top - _bottom), 0, -(_top + _bottom) / (_top - _bottom), 0, 0,
            -2 / (_far - _near), -(_far + _near) / (_far - _near), 0, 0, 0, 1)),
        left(_left), right(_right), top(_top), bottom(_bottom), near(_near),
        far(_far) {};
};

} // namespace t

#endif // ORTHOGRAPHICCAMERA_HPP
