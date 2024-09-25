#include "materials/Material.hpp"

#ifndef NORMALCOLOR_HPP
#define NORMALCOLOR_HPP

namespace t {

/**
 * A material that maps the mesh's world normal vectors to normalized RGB
 * colors.
 */
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
    return Color((uniforms.normalMatrix * varyings.localNormal).absolute());
  }
};

} // namespace t

#endif // NORMALCOLOR_HPP
