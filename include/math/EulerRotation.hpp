#include "constants.hpp"

#ifndef EULERROTATION_HPP
#define EULERROTATION_HPP

namespace t {

class EulerRotation {
public:
  double x;
  double y;
  double z;
  EulerRotationOrder order;

  EulerRotation(double _x, double _y, double _z, EulerRotationOrder _order)
      : x(_x), y(_y), z(_z), order(_order) {}

  EulerRotation &copy(const EulerRotation &source) {
    x = source.x;
    y = source.y;
    z = source.z;
    order = source.order;

    return *this;
  }

  friend EulerRotation operator+(const EulerRotation &a,
                                 const EulerRotation &b) {
    return EulerRotation(a.x + b.x, a.y + b.y, a.z + b.z, a.order);
  }

  friend EulerRotation operator-(const EulerRotation &a,
                                 const EulerRotation &b) {
    return EulerRotation(a.x - b.x, a.y - b.y, a.z - b.z, a.order);
  }
};

} // namespace t

#endif // EULERROTATION_HPP