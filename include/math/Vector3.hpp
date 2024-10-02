#include "primitives/BufferAttribute.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace t {

/**
 * The 3D vector class.
 *
 * A 3D vector is a triplet of numbers labeled x, y, and z which can be used to
 * represent a number of things e.g. 3D coordinates, Euler angles, RGB colors,
 * etc.
 *
 * \ingroup math
 */
class Vector3 {
public:
  double x; /**< The x component of this 3D vector. */
  double y; /**< The y component of this 3D vector. */
  double z; /**< The z component of this 3D vector. */

  /**
   * Returns 3 consecutive values at the specified index in a {@link
   * BufferAttribute} at the specified in a {@code Vector3}.
   *
   * @param bufferAttribute The attribute to get the values from.
   * @param index The index of the first value in the index.
   * @returns A new {@code Vector3} with 3 consecutive values starting at the
   * specified index.
   */
  static Vector3
  fromBufferAttribute(const BufferAttribute<double> &bufferAttribute,
                      int index) {
    return Vector3(
        bufferAttribute.array.at(index * bufferAttribute.itemSize),
        bufferAttribute.array.at(index * bufferAttribute.itemSize + 1),
        bufferAttribute.array.at(index * bufferAttribute.itemSize + 2));
  }

  /**
   * Returns the [cross product](https://en.wikipedia.org/wiki/Cross_product) of
   * two vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   * @returns The cross product of the two vectors.
   */
  // TODO: make this method an instance method
  static Vector3 cross(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x,
                   a.x * b.y - b.x * a.y);
  }

  /**
   * Returns the [dot product](https://en.wikipedia.org/wiki/Dot_product) of two
   * vectors.
   *
   * @param a The first vector.
   * @param b The second vector.
   * @returns The dot product of the two vectors.
   */
  // TODO: make this method an instance method
  static double dot(const Vector3 &a, const Vector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  /**
   * Returns the reflection of an incident vector off a surface that has the
   * specified orientation.
   *
   * The reflection is calculated as \f$\vec{v} - 2 \cdot (\vec{s} \cdot
   * \vec{v}) \cdot \vec{s}\f$ where \f$\vec{v}\f$ is the incident vector and
   * \f$\vec{s}\f$ is the surface orientation.
   *
   * @param incident The incident vector.
   * @param surfaceOrientation The surface orientation.
   * @returns The reflection of the incident vector off the surface.
   */
  static Vector3 reflect(const Vector3 &incident,
                         const Vector3 &surfaceOrientation) {
    return incident -
           2.0 * dot(surfaceOrientation, incident) * surfaceOrientation;
  }

  /**
   * Creates a new 3D vector with the specified components.
   *
   * @param _x The x component of the new 3D vector.
   * @param _y The y component of the new 3D vector.
   * @param _z The z component of the new 3D vector.
   */
  Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

  /**
   * Returns a copy of this 3D vector.
   *
   * @returns A new 3D vector with the same components as this vector.
   */
  Vector3 clone() const { return Vector3(x, y, z); }

  /**
   * Copies the components of the specified 3D vector to this 3D vector.
   *
   * @param source A 3D vector to copy the components from.
   * @returns This vector.
   */
  Vector3 &copy(const Vector3 &source) {
    x = source.x;
    y = source.y;
    z = source.z;

    return *this;
  }

  /**
   * Sets the components of this vector.
   *
   * @param _x The new x component.
   * @param _y The new y component.
   * @param _z The new z component.
   */
  Vector3 &set(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;

    return *this;
  }

  /**
   * Returns the length of this 3D vector.
   *
   * Specifically, returns the [Euclidean
   * length](https://en.wikipedia.org/wiki/Euclidean_distance).
   *
   * @returns The length of this vector.
   */
  double length() const { return std::sqrt(x * x + y * y + z * z); }

  /**
   * Returns the unit vector of this 3D vector.
   *
   * @returns The unit vector of this vector.
   */
  Vector3 unit() const { return *this / length(); }

  /**
   * Normalizes this 3D vector.
   *
   * Note that this method modifies this instance. If you want to avoid
   * modification, use {@link #unit} instead.
   *
   * @returns This vector.
   */
  Vector3 &normalize() {
    *this /= length();
    return *this;
  }

  /**
   * Returns a new 3D vector with the absolute values of the components of this
   * 3D vector.
   *
   * @returns A new vector with the absolute values of the components of this
   * vector.
   */
  Vector3 absolute() const {
    return Vector3(std::abs(x), std::abs(y), std::abs(z));
  }

  /**
   * Sets the components of this 3D vector to their absolute values.
   *
   * Note that this method modifies this instance. If you want to avoid
   * modification, use {@link #absolute} instead.
   *
   * @returns This vector.
   */
  Vector3 &abs() {
    x = std::abs(x);
    y = std::abs(y);
    z = std::abs(z);

    return *this;
  }

  /**
   * Clamps the components of this 3D vector to the specified minimum and
   * maximum 3D vectors component-wise.
   *
   * @param min The minimum 3D vector.
   * @param max The maximum 3D vector.
   * @returns This vector.
   */
  Vector3 &clamp(const Vector3 &min, const Vector3 &max) {
    x = std::clamp(x, min.x, max.x);
    y = std::clamp(y, min.y, max.y);
    z = std::clamp(z, min.z, max.z);

    return *this;
  }

  /**
   * Clamps the components of this 3D vector to the specified minimum and
   * maximum values.
   *
   * @param min The minimum value.
   * @param max The maximum value.
   * @returns This vector.
   */
  Vector3 &clamp(double min, double max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);

    return *this;
  }

  /**
   * Returns the component at the specified index of this 3D vector.
   *
   * @param index A 0-based index. Must be 0, 1, or 2.
   * @returns The component at `index`.
   * @throws std::invalid_argument if `index` is not 0, 1, or 2.
   */
  double operator[](std::size_t index) const {
    switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::invalid_argument("Index to Vector3 must be 0, 1, or 2.");
    }
  }

  /**
   * Adds the specified 3D vector to this vector.
   *
   * @param v A 3D vector.
   * @returns This vector.
   */
  Vector3 &operator+=(const Vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
  }

  /**
   * Adds the specified constant to all components in this 3D vector.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector3 &operator+=(double s) {
    x += s;
    y += s;
    z += s;

    return *this;
  }

  /**
   * Subtracts the specified 3D vector from this vector.
   *
   * @param v A 3D vector.
   * @returns This vector.
   */
  Vector3 &operator-=(const Vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
  }

  /**
   * Subtracts the specified constant from all components in this 3D vector.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector3 &operator-=(double s) {
    x -= s;
    y -= s;
    z -= s;

    return *this;
  }

  /**
   * Multiplies the components of this vector with the corresponding components
   * of the specified 3D vector.
   *
   * @param v A 3D vector.
   * @returns This vector.
   *
   * @see #dot
   * @see #cross
   */
  Vector3 &operator*=(const Vector3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;

    return *this;
  }

  /**
   * Multiplies all components of this 3D vector with the specified constant.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector3 &operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;

    return *this;
  }

  /**
   * Divides the components of this vector by the corresponding components of
   * another 3D vector
   *
   * @param v A 3D vector.
   * @returns This vector.
   */
  Vector3 &operator/=(const Vector3 &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;

    return *this;
  }

  /**
   * Divides the components of this 3D vector by the specified constant.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector3 &operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;

    return *this;
  }

  /**
   * Returns whether if two 3D vectors are equal.
   *
   * @returns `true` if the two vectors are equal, `false` otherwise.
   */
  friend bool operator==(const Vector3 &a, const Vector3 &b) = default;

  /**
   * Returns the negation of this 3D vector.
   *
   * @returns The negation of this 3D vector.
   */
  friend Vector3 operator-(const Vector3 &a) { return a * -1; }

  /**
   * Adds two 3D vectors.
   *
   * @param a A 3D vector.
   * @param b Another 3D vector.
   * @returns The sum of `a` and `b`.
   */
  friend Vector3 operator+(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  /**
   * Adds a constant to all components of a 3D vector.
   *
   * @param a A 3D vector.
   * @param s A constant.
   * @returns The resulting vector when adding `s` to the components of `a`.
   */
  friend Vector3 operator+(const Vector3 &a, double s) {
    return Vector3(a.x + s, a.y + s, a.z + s);
  }

  /**
   * Adds a constant to all components of a 3D vector.
   *
   * @param s A constant.
   * @param a A 3D vector.
   * @returns The resulting vector when adding `s` to the components of `a`.
   */
  friend Vector3 operator+(double s, const Vector3 &a) { return a + s; }

  /**
   * Subtracts two 3D vectors.
   *
   * @param a A 3D vector.
   * @param b Another 3D vector.
   * @returns The difference of `a` and `b`.
   */
  friend Vector3 operator-(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
  }

  /**
   * Subtracts a constant from all components of a 3D vector.
   *
   * @param a A 3D vector.
   * @param s A constant.
   * @returns The resulting vector when subtracting `s` from the components of
   * `a`.
   */
  friend Vector3 operator-(const Vector3 &a, double s) {
    return Vector3(a.x - s, a.y - s, a.z - s);
  }

  /**
   * Subtracts a 3D vector from a constant 3D vector.
   *
   * A constant vector is a vector whose components are all the same.
   *
   * @param s A constant for the constant 3D vector.
   * @param a A 3D vector.
   * @returns The resulting vector when subtracting the components of `a` from
   * the constant vector of `s`.
   */
  friend Vector3 operator-(double s, const Vector3 &a) {
    return Vector3(s - a.x, s - a.y, s - a.z);
  }

  /**
   * Returns the element-wise product of two 3D vectors, also known as the
   * [Hadamard
   * product](https://en.wikipedia.org/wiki/Hadamard_product_(matrices)).
   *
   * @param a A 3D vector.
   * @param b Another 3D vector.
   * @returns The element-wise product of `a` and `b`.
   */
  friend Vector3 operator*(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
  }

  /**
   * Multiplies all components of a 3D vector with a constant.
   *
   * @param a A 3D vector.
   * @param s A constant.
   * @returns The resulting vector when multiplying the components of `a` with
   * `s`.
   */
  friend Vector3 operator*(const Vector3 &a, double s) {
    return Vector3(a.x * s, a.y * s, a.z * s);
  }

  /**
   * Multiplies all components of a 3D vector with a constant.
   *
   * @param s A constant.
   * @param a A 3D vector.
   * @returns The resulting vector when multiplying the components of `a` with
   * `s`.
   */
  friend Vector3 operator*(double s, const Vector3 &a) { return a * s; }

  /**
   * Returns the element-wise division of two 3D vectors.
   *
   * @param a A 3D vector.
   * @param b Another 3D vector.
   * @returns The element-wise division `a` and `b`.
   */
  friend Vector3 operator/(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
  }

  /**
   * Divides the components of a 3D vector by a constant.
   *
   * @param a A 3D vector.
   * @param s A constant.
   * @returns The resulting vector when dividing the components of `a` by `s`.
   */
  friend Vector3 operator/(const Vector3 &a, double s) {
    return Vector3(a.x / s, a.y / s, a.z / s);
  }

  /**
   * Returns the element-wise division of a constant 3D vector and a 3D vector.
   *
   * A constant vector is a vector whose components are all the same.
   *
   * @param s A constant for the constant 3D vector.
   * @param a A 3D vector.
   * @returns The element-wise division of the constant 3D vector and `a`.
   */
  friend Vector3 operator/(double s, const Vector3 &a) {
    return Vector3(s / a.x, s / a.y, s / a.z);
  }
};

} // namespace t

#endif // VECTOR3_HPP
