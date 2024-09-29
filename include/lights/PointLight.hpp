#include "lights/Light.hpp"
#include "primitives/Color.hpp"

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

namespace t {

/**
 * The point light, which gets emitted from a single point in all directions.
 *
 * Point lights are some of the most common lights in 3D graphics. They can be
 * used, for example, to represent lights from light bulbs or fireflies.
 *
 * For the {@link BlinnPhong} material, the light's color contribution will be
 * \f$c = \text{diffuse color} \times \text{light's intensity} \times
 * (\text{specular} + \text{diffuse})\f$. The specular and diffuse components do
 * not rely on the light's intensity.
 *
 * \ingroup lights
 */
class PointLight : public Light {
public:
  Color color;      /**< The color of this point light. */
  double intensity; /**< The intensity of this point light in candela (cd). */

  /**
   * Creates a new point light with the specified color and intensity.
   *
   * @param color The color of the new point light.
   * @param intensity The intensity of the new point light in candela (cd).
   */
  PointLight(Color color, double intensity)
      : color(color), intensity(intensity) {}

  /**
   * Returns whether or not this light is a point light.
   *
   * Always returns `true`. May be used in vertex and fragment shaders to
   * determine the type of light and make a cast from {@link Light}
   * appropriately.
   *
   * @returns `true`
   */
  bool isPointLight() const override { return true; }

  /**
   * Returns the power of this light.
   *
   * The power of this light is in lumens (lm) and is calculated as
   * \f$\text{intensity} \times 4 \times \pi\f$.
   *
   * @returns The power of this light in lumens (lm).
   */
  double power() const { return intensity * 4 * M_PI; }
};

} // namespace t

#endif // POINTLIGHT_HPP