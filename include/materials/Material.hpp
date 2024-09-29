#include "lights/Light.hpp"
#include "primitives/Attributes.hpp"
#include "primitives/Color.hpp"
#include "primitives/Uniforms.hpp"
#include "primitives/Varyings.hpp"

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

namespace t {

/**
 * The base material class.
 *
 * A material defines the look of a 3D object. It is one of the 2 components of
 * a {@linkplain Mesh 3D mesh}.
 *
 * This class must not be instantiated directly. Instead, you can create your
 * own material by deriving from this class and implement your own {@link
 * #vertexShader} and {@link #fragmentShader}.
 *
 * \ingroup materials
 */
class Material {
public:
  CullMode cullMode =
      CullMode::Back;     /**< The face to cull (not draw) in the render. */
  bool depthTest = true;  /**< Whether or not to perform the depth test. The
                             depth test tests if a part of an object is behind
                             another object, and thus avoid drawing that part. */
  bool depthWrite = true; /**< Whether or not to write the depth of the object
                             to the depth texture. */

  virtual ~Material() = default;

  /**
   * The vertex shader of this material, which will be run for every vertex of
   * the mesh's geometry.
   *
   * @param uniforms The uniforms.
   * @param attributes The attributes of the vertex.
   * @returns The transformed vertex's position in homogeneous coordinates,
   * usually in normalized device coordinates (NDC).
   */
  virtual Vector4 vertexShader(const Uniforms &uniforms,
                               const Attributes &attributes) = 0;

  /**
   * The fragment shader of this material, which will be run for every fragment
   * that the mesh covers on the screen to determine its color.
   *
   * @param uniforms The uniforms.
   * @param varyings The varyings.
   * @param lights The list of lights in the scene.
   * @returns The color of the fragment this shader is invoked on.
   *
   * @see Fragment
   */
  virtual Color
  fragmentShader(const Uniforms &uniforms, const Varyings &varyings,
                 const std::vector<std::reference_wrapper<Light>> &lights) = 0;
};

} // namespace t

#endif // MATERIAL_HPP