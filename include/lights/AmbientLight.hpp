#include "lights/Light.hpp"
#include "primitives/Color.hpp"

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

namespace t {

/**
 * A light that illuminates all objects in the scene equally.
 *
 * Ambient lighting is used in many ways, such as providing a base level of
 * illumination in a dark scene where you don't want the scene to be completely
 * dark. It is also a component of the [Phong reflection
 * model](https://en.wikipedia.org/wiki/Phong_reflection_model).
 *
 * For the {@link BlinnPhong} material, the light's color contribution will be
 * \f$c = c_{o} \times c_{l} \times s\f$ where:
 * - \f$c\f$ is the light's color contribution to the object's appearance;
 * - \f$c_{o}\f$ is the {@linkplain BlinnPhong#color material's color};
 * - \f$c_{l}\f$ is {@linkplain #color the color of the ambient light};
 * - \f$s\f$ is {@linkplain #intensity the intensity of the ambient light}.
 *
 * \ingroup lights
 */
class AmbientLight : public Light {
public:
  Color color;      /**< The color of this ambient light. */
  double intensity; /**< The intensity of this ambient light. */

  /**
   * Creates a new ambient light with the specified color and intensity.
   *
   * @param _color The color of the new ambient light.
   * @param _intensity The intensity of the new ambient light. `0` means the
   * ambient light will have no effect. `1` means full intensity.
   */
  AmbientLight(Color _color, double _intensity)
      : color(_color), intensity(_intensity) {};

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