#include "math/Vector3.hpp"
#include <algorithm>

#ifndef COLOR_HPP
#define COLOR_HPP

namespace t {

class Color : public Vector3 {
public:
  using Vector3::Vector3;

  Color(int r, int g, int b, int colorDepth = 8)
      : Vector3(r / std::pow(2, colorDepth), g / std::pow(2, colorDepth),
                b / std::pow(2, colorDepth)) {}

  explicit Color(Vector3 vector3) : Vector3(vector3.x, vector3.y, vector3.z) {}

  Color &clamp() {
    x = std::clamp(x, 0.0, 1.0);
    y = std::clamp(y, 0.0, 1.0);
    z = std::clamp(z, 0.0, 1.0);

    return *this;
  }

  double luminance() const { return x * 0.2126 + y * 0.7152 + z * 0.0722; }
};

} // namespace t

#endif // COLOR_HPP