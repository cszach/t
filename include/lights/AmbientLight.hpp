#include "lights/Light.hpp"
#include "primitives/Color.hpp"

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

namespace t {

/**
 * A light that illuminates all objects in the scene equally.
 *
 * For the {@link BlinnPhong} material, the light's color contribution will be
 * the 3D object's color multiplied by the light's color multiplied by the
 * light's intensity. The light's intensity is unitless.
 */
class AmbientLight : public Light {
public:
  Color color;      /**< The color of this ambient light. */
  double intensity; /**< The intensity of this ambient light. */

  /**
   * Creates a new ambient light with the specified color and intensity.
   */
  AmbientLight(
      Color color /**< [in] The color of the new ambient light. */,
      double intensity /**< [in] The intensity of the new ambient light. */)
      : color(color), intensity(intensity) {};

  /**
   * Returns whether or not this light is an ambient light.
   *
   * Always returns `true`. May be used in vertex and fragment shaders to
   * determine the type of light and make a cast from {@link Light}
   * appropriately.
   */
  bool isAmbientLight() const override { return true; }
};

} // namespace t

#endif // AMBIENTLIGHT_HPP