#include "lights/Light.hpp"
#include "primitives/Attributes.hpp"
#include "primitives/Color.hpp"
#include "primitives/Uniforms.hpp"
#include "primitives/Varyings.hpp"

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

namespace t {

class Material {
public:
  CullMode cullMode = CullMode::Back;
  bool depthTest = true;
  bool depthWrite = true;

  virtual ~Material() = default;
  virtual Vector4 vertexShader(const Uniforms &uniforms,
                               const Attributes &attributes) = 0;
  virtual Color
  fragmentShader(const Uniforms &uniforms, const Varyings &varyings,
                 const std::vector<std::reference_wrapper<Light>> &lights) = 0;
};

} // namespace t

#endif // MATERIAL_HPP