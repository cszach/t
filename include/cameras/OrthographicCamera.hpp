#include "cameras/Camera.hpp"

#ifndef ORTHOGRAPHICCAMERA_HPP
#define ORTHOGRAPHICCAMERA_HPP

namespace t {

/**
 * A camera that uses [orthographic
 * projection](https://en.wikipedia.org/wiki/Orthographic_projection).
 *
 * A typical orthographic camera instantiation might look like the following:
 *
 * ```cpp
 * const auto width = 80; // The width of the output image in pixels
 * const auto height = 24; // The height of the output image in pixels
 *
 * const auto camera = OrthographicCamera(width / -2.0, width / 2.0, height
 * / 2.0, height / -2.0, 0.1, 2000 );
 * ```
 */
class OrthographicCamera : public Camera {
public:
  double left;   /**< The left plane of the view frustum. */
  double right;  /**< The right plane of the view frustum. */
  double top;    /**< The top plane of the view frustum. */
  double bottom; /**< The bottom plane of the view frustum. */
  double near;   /**< The near plane of the view frustum. */
  double far;    /**< The far plane of the view frustum. */

  /**
   * Creates a new orthographic camera with the specified planes as the [view
   * frustum](https://en.wikipedia.org/wiki/Viewing_frustum).
   *
   * The view frustum of the orthographic camera is in the shape of a cuboid.
   * Only objects in this cuboid may appear in the render.
   *
   * The planes should be set such that `_right` > `_left` and `_top > _bottom`.
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