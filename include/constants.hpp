#include "math/Vector3.hpp"

/**
 * \file constants.hpp
 * Contains various constants and enumerations.
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace t {

/**
 * The Euler rotation order.
 *
 * For example, `EulerRotationOrder::Xyz` means that the x rotation is applied
 * first, then y, then z.
 */
enum class EulerRotationOrder { Xyz, Xzy, Yxz, Yzx, Zxy, Zyx };

/**
 * The texture format.
 *
 * The integer associated with the format is the number of components in the
 * texture. For example, `TextureFormat::RgbDouble = 3` because it has 3
 * components (RGB).
 */
enum class TextureFormat {
  RgbDouble = 3 /**< Stores RGB values in normalized floating-point values. */,
  Depth = 1 /**< Stores the depth in normalized floating-point values. */
};

/**
 * The winding order that determines the front face of a triangle.
 */
enum class FrontFace { Clockwise = 1, CounterClockwise = -1 };

/**
 * Which faces to cull in the render.
 */
enum class CullMode {
  None = 0 /**< Renders both front and back faces. */,
  Front = 1 /**< Culls front faces. */,
  Back = -1 /**< Culls back faces. */
};

/**
 * The default up direction.
 */
#define DEFAULT_UP Vector3(0, 1, 0)

} // namespace t

#endif // CONSTANTS_HPP