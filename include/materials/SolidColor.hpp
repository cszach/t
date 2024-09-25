#include "materials/Material.hpp"

#ifndef SOLIDCOLOR_HPP
#define SOLIDCOLOR_HPP

namespace t {

/**
 * A material that appears in one single color and unaffected by lights.
 */
class SolidColor : public Material {
public:
  Color color; /**< The color of the material. */

  ~SolidColor() override = default;

  /**
   * Creates a new solid color material.
   *
   * @param _color The color of the new material.
   */
  explicit SolidColor(Color _color) : color(_color) {}

  Vector4 vertexShader(const Uniforms &uniforms,
                       const Attributes &attributes) override {
    return uniforms.projectionMatrix * uniforms.modelViewMatrix *
           Vector4(attributes.localPosition, 1.0);
  }

  Color fragmentShader(
      const Uniforms &uniforms, const Varyings &varyings,
      const std::vector<std::reference_wrapper<Light>> &lights) override {
    return this->color;
  }
};

} // namespace t

#endif // SOLIDCOLOR_HPP