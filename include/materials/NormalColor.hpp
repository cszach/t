#include "materials/Material.hpp"

#ifndef NORMALCOLOR_HPP
#define NORMALCOLOR_HPP

namespace t {

class NormalColor : public Material {
public:
  Vector4 vertexShader(const Uniforms &uniforms,
                       const Attributes &attributes) override {
    return uniforms.projectionMatrix * uniforms.modelViewMatrix *
           Vector4(attributes.localPosition, 1.0);
  }

  Color fragmentShader(
      const Uniforms &uniforms, const Varyings &varyings,
      const std::vector<std::reference_wrapper<Light>> &lights) override {
    return Color(varyings.localNormal.absolute());
  }
};

} // namespace t

#endif // NORMALCOLOR_HPP
