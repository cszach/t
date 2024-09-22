#include "lights/Light.hpp"
#include "primitives/Color.hpp"

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

namespace t {

class AmbientLight : public Light {
public:
  Color color;
  double intensity;

  AmbientLight(Color color, double intensity)
      : color(color), intensity(intensity) {};

  bool isAmbientLight() const override { return true; }
};

} // namespace t

#endif // AMBIENTLIGHT_HPP