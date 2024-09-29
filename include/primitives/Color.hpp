#include "math/Vector3.hpp"
#include <algorithm>

#ifndef COLOR_HPP
#define COLOR_HPP

namespace t {

/**
 * The color class.
 *
 * The class inherits from {@link Vector3} and the x, y, and z components map to
 * the **normalized** red, green, and blue components of the color,
 * respectively.
 *
 * \ingroup primitives
 */
class Color : public Vector3 {
public:
  using Vector3::Vector3;

  /**
   * Creates a new color with the specified _normalized_ red, green, and blue
   * components.

   * The components should be in the range \f$[0, 1]\f$.
   *
   * ```cpp
   * auto red = Color(1, 0, 0);
   * auto green = Color(0, 1, 0);
   * auto blue = Color(0, 0, 1);
   * auto white = Color(1, 1, 1);
   * ```
   *
   * @param r The normalized red component of the color.
   * @param g The normalized green component of the color.
   * @param b The normalized blue component of the color.
   */
  Color(double r, double g, double b) : Vector3(r, g, b) {}

  /**
   * Creates a new color with the specified red, green, and blue components and
   * the specified color depth.
   *
   * The components should be in the range \f$[0, 2^{d} - 1]\f$ where \f$d\f$ is
   * the color depth.
   *
   * ```cpp
   * auto red = Color(255, 0, 0); // 8-bit red color
   * auto green16 = Color(0, 65535, 0, 16); // 16-bit green color
   * auto white = Color(255, 255, 255); // 8-bit white color
   * ```
   *
   * @param r The red component of the color.
   * @param g The green component of the color.
   * @param b The blue component of the color.
   * @param colorDepth The color depth of the color.
   */
  Color(int r, int g, int b, int colorDepth = 8)
      : Vector3(r / std::pow(2, colorDepth), g / std::pow(2, colorDepth),
                b / std::pow(2, colorDepth)) {}

  /**
   * Creates a new color with the specified {@link Vector3} components as
   * normalized RGB values.
   *
   * @param vector3 The {@link Vector3} with the normalized red, green, and blue
   * components.
   */
  explicit Color(Vector3 vector3) : Vector3(vector3.x, vector3.y, vector3.z) {}

  /**
   * Clamps the components of this color to the range \f$[0, 1]\f$.
   *
   * @returns This color.
   */
  Color &clamp() {
    Vector3::clamp(0, 1);
    return *this;
  }

  /**
   * Returns the luminance of this color.
   *
   * The luminance is calculated as \f$0.2126r + 0.7152g + 0.0722z\f$
   * ([reference](https://stackoverflow.com/a/56678483)).
   *
   * @returns The luminance of this color.
   */
  double luminance() const { return x * 0.2126 + y * 0.7152 + z * 0.0722; }
};

} // namespace t

#endif // COLOR_HPP