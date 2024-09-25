#include "materials/Material.hpp"
#include <cmath>

#ifndef BLINNPHONG_HPP
#define BLINNPHONG_HPP

namespace t {

/**
 * A shiny material that uses the [Blinn-Phong reflection
 * model](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model).
 */
class BlinnPhong : public Material {
public:
  Color diffuseColor;  /**< The base color of the material. */
  Color specularColor; /**< The color of the specular highlights. */
  double shininess;    /**< The shininess index of the material. */

  /**
   * Creates a new shiny material with the specified diffuse color, specular
   * color, and shininess.
   *
   * @param _diffuseColor The base color of the material.
   * @param _specularColor The color of the specular highlights.
   * @param _shininess The shininess index of the material.
   */
  BlinnPhong(Color _diffuseColor, Color _specularColor, double _shininess)
      : diffuseColor(_diffuseColor), specularColor(_specularColor),
        shininess(_shininess) {};

  Vector4 vertexShader(const Uniforms &uniforms,
                       const Attributes &attributes) override {
    return uniforms.projectionMatrix * uniforms.modelViewMatrix *
           Vector4(attributes.localPosition, 1.0);
  }

  Color fragmentShader(
      const Uniforms &uniforms, const Varyings &varyings,
      const std::vector<std::reference_wrapper<Light>> &lights) override {
    Color outputColor(0, 0, 0);

    for (Light &light : lights) {
      if (light.isAmbientLight()) {
        const auto ambientLight = dynamic_cast<AmbientLight &>(light);
        const auto ambient = ambientLight.intensity * ambientLight.color;

        outputColor += ambient * diffuseColor;
      } else if (light.isPointLight()) {
        const auto pointLight = dynamic_cast<PointLight &>(light);

        const auto fragWorldPosition =
            (uniforms.modelMatrix * Vector4(varyings.localPosition, 1))
                .toVector3();
        const auto lightWorldPosition =
            (light.modelMatrix * Vector4(light.localPosition, 1)).toVector3();
        const auto worldNormal =
            (uniforms.normalMatrix * varyings.localNormal).normalize();

        const auto lightDirection = lightWorldPosition - fragWorldPosition;
        const double distance = Vector3::dot(lightDirection, lightDirection);
        lightDirection.unit();

        auto lambertian =
            std::max(Vector3::dot(lightDirection, worldNormal), 0.0);
        auto specular = 0.0;

        if (lambertian > 0) {
          const auto viewDirection =
              (uniforms.cameraPosition - fragWorldPosition).normalize();
          const auto halfway = (lightDirection + viewDirection).normalize();
          const auto specularAngle =
              std::max(Vector3::dot(halfway, worldNormal), 0.0);
          specular = std::pow(specularAngle, shininess);
        }

        outputColor += diffuseColor * lambertian * pointLight.color *
                           pointLight.power() / distance +
                       specularColor * specular * pointLight.color *
                           pointLight.power() / distance;
      }
    }

    return outputColor;
  }
};

} // namespace t

#endif // BLINNPHONG_HPP