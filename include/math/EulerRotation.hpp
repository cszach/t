#include "constants.hpp"

#ifndef EULERROTATION_HPP
#define EULERROTATION_HPP

namespace t {

/**
 * A class that represents [Euler
 * rotations](https://en.wikipedia.org/wiki/Euler_angles).
 *
 * An Euler rotation is represented by 3 rotations about the local X, Y, and Z
 * axes, executed in a certain order. Note that if the 3 rotations are the same
 * but the execution order is different, we might get a different rotation.
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
   * @param source A reference to a Euler rotation.
   * @returns A reference to this Euler rotation.
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
   * @param a A reference to an Euler rotation.
   * @param b A reference to an Euler rotation.
   * @returns The result of adding `a` and `b`.
   */
  friend EulerRotation operator+(const EulerRotation &a,
                                 const EulerRotation &b) {
    return EulerRotation(a.x + b.x, a.y + b.y, a.z + b.z, a.order);
  }

  /**
   * Substracts an Euler rotation from another Euler rotation.
   *
   * @param a A reference to the Euler rotation to subtract from.
   * @param b A reference to the Euler rotation to subtract from `a`.
   * @returns The result of the subtraction.
   */
  friend EulerRotation operator-(const EulerRotation &a,
                                 const EulerRotation &b) {
    return EulerRotation(a.x - b.x, a.y - b.y, a.z - b.z, a.order);
  }
};

} // namespace t

#endif // EULERROTATION_HPP