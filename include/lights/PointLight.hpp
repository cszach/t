#include "lights/Light.hpp"
#include "primitives/Color.hpp"

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

namespace t {

/**
 * A light that gets emitted from a single point in all directions.
 *
 * Point lights are some of the most common lights in 3D graphics. They can be
 * used, for example, to represent lights from light bulbs or fireflies.
 *
 * For the {@link BlinnPhong} material, the light's color contribution will be
 * the 3D object's color multiplied by the light's intensity multiplied by the
 * sum of the specular and diffuse components (which do not rely on the light's
 * intensity). The light's intensity is unitless.
 */
class PointLight : public Light {
public:
  Color color;      /**< The color of this point light. */
  double intensity; /**< The intensity of this point light. */

  /**
   * Creates a new point light with the specified color and intensity.
   */
  PointLight(
      Color color /**< [in] The color of the new point light. */,
      double intensity /**< [in] The intensity of the new point light. */)
      : color(color), intensity(intensity) {}

  /**
   * Returns whether or not this light is a point light.
   *
   * Always returns `true`. May be used in vertex and fragment shaders to
   * determine the type of light and make a cast from {@link Light}
   * appropriately.
   */
  bool isPointLight() const override { return true; }

  double power() const { return intensity * 4 * M_PI; }
};

} // namespace t

#endif // POINTLIGHT_HPP