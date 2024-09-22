#include "lights/Light.hpp"
#include "primitives/Color.hpp"

#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

namespace t {

class PointLight : public Light {
public:
  Color color;
  double intensity;

  PointLight(Color color, double intensity)
      : color(color), intensity(intensity) {}

  bool isPointLight() const override { return true; }
};

} // namespace t

#endif // POINTLIGHT_HPP