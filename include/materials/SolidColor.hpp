#include "materials/Material.hpp"

#ifndef SOLIDCOLOR_HPP
#define SOLIDCOLOR_HPP

namespace t {

class SolidColor : public Material {
public:
  Color color;

  ~SolidColor() override = default;

  explicit SolidColor(Color color) : color(color) {}

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