#include "constants.hpp"

#ifndef EULERROTATION_HPP
#define EULERROTATION_HPP

namespace t {

/**
 * The [Euler rotation](https://en.wikipedia.org/wiki/Euler_angles) class.
 *
 * An Euler rotation is represented by 3 rotations about the local X, Y, and Z
 * axes, executed in a certain order. Note that if the 3 rotations are the same
 * but the execution order is different, we might get a different rotation.
 *
 * \ingroup math
 */
class EulerRotation {
public:
  double x; /**< The amount of rotation about the local X axis in radians. */
  double y; /**< The amount of rotation about the local Y axis in radians. */
  double z; /**< The amount of rotation about the local Z axis in radians. */
  EulerRotationOrder
      order; /**< The order to perform the rotations around individual axes. */

  /**
   * Creates a new representation of a rotation based on Euler angles.
   *
   * @param _x The amount of rotation about the local X axis in radians.
   * @param _y The amount of rotation about the local Y axis in radians.
   * @param _z The amount of rotation about the local Z axis in radians.
   * @param _order The order to perform the rotations around individual axes.
   */
  EulerRotation(double _x, double _y, double _z, EulerRotationOrder _order)
      : x(_x), y(_y), z(_z), order(_order) {}

  /**
   * Copies another Euler rotation into this Euler rotation.
   *
   * @param source The Euler rotation to copy from.
   * @returns This Euler rotation.
   */
  EulerRotation &copy(const EulerRotation &source) {
    x = source.x;
    y = source.y;
    z = source.z;
    order = source.order;

    return *this;
  }

  /**
   * Adds 2 Euler rotations.
   *
   * @param a An Euler rotation.
   * @param b Another Euler rotation.
   * @returns The result of adding `a` and `b`.
   */
  friend EulerRotation operator+(const EulerRotation &a,
                                 const EulerRotation &b) {
    return EulerRotation(a.x + b.x, a.y + b.y, a.z + b.z, a.order);
  }

  /**
   * Substracts an Euler rotation from another Euler rotation.
   *
   * @param a An Euler rotation.
   * @param b Another Euler rotation.
   * @returns The difference of `a` and `b`.
   */
  friend EulerRotation operator-(const EulerRotation &a,
                                 const EulerRotation &b) {
    return EulerRotation(a.x - b.x, a.y - b.y, a.z - b.z, a.order);
  }
};

} // namespace t

#endif // EULERROTATION_HPP