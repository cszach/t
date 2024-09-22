#include "materials/Material.hpp"
#include <cmath>

#ifndef BLINNPHONG_HPP
#define BLINNPHONG_HPP

namespace t {

class BlinnPhong : public Material {
public:
  Color color;
  Color specularColor;
  double shininess;

  explicit BlinnPhong(Color color, Color specularColor, double shininess)
      : color(color), specularColor(specularColor), shininess(shininess) {};

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

        outputColor += ambient * color;
      } else if (light.isPointLight()) {
        const auto pointLight = dynamic_cast<PointLight &>(light);
        const auto fragWorldPosition =
            (uniforms.modelMatrix * Vector4(varyings.localPosition, 1))
                .toVector3();
        const auto lightWorldPosition =
            (light.modelMatrix * Vector4(light.localPosition, 1)).toVector3();
        const auto worldNormal =
            (uniforms.normalMatrix * varyings.localNormal).normalize();

        const auto lightDirection =
            (lightWorldPosition - fragWorldPosition).normalize();
        const auto viewDirection =
            (uniforms.cameraPosition - fragWorldPosition).normalize();
        const auto reflectDirection =
            Vector3::reflect(-lightDirection, worldNormal);

        const auto diffuse =
            std::max(Vector3::dot(worldNormal, lightDirection), 0.0);
        const auto diffuseColor = pointLight.color * diffuse;

        const auto specular = std::pow(
            std::max(Vector3::dot(viewDirection, reflectDirection), 0.0),
            shininess);
        const auto spec = specularColor * specular;

        outputColor += (diffuseColor + spec) * pointLight.intensity * color;
      }
    }

    return outputColor;
  }
};

} // namespace t

#endif // BLINNPHONG_HPP