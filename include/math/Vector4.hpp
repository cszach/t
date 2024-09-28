#include "math/Vector3.hpp"

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace t {

#define m matrix4.elements
#define v vector4

/**
 * The 4D vector class.
 *
 * A 4D vector is a triplet of numbers labeled x, y, z, and w which can be used
 * to represent a number of things e.g. 4D homogeneous coordinates, RGBA colors,
 * etc.
 */
class Vector4 {
public:
  double x; /**< The x component of this 4D vector. */
  double y; /**< The y component of this 4D vector. */
  double z; /**< The w component of this 4D vector. */
  double w; /**< The z component of this 4D vector. */

  /**
   * Creates a new 4D vector with the specified components.
   *
   * @param _x The x component of the new 4D vector.
   * @param _y The y component of the new 4D vector.
   * @param _z The z component of the new 4D vector.
   * @param _w The w component of the new 4D vector.
   */
  Vector4(double _x, double _y, double _z, double _w)
      : x(_x), y(_y), z(_z), w(_w) {}

  /**
   * Creates a new 4D vector with the same x, y, and z components as the
   * specified 3D vector and the specified w component.
   *
   * @param vector3 A 3D vector to copy the x, y, and z components from.
   * @param w The w component of the new 4D vector.
   */
  Vector4(const Vector3 &vector3, double w)
      : Vector4(vector3.x, vector3.y, vector3.z, w) {}

  /**
   * Returns a copy of this 4D vector.
   *
   * @returns A new 4D vector with the same components as this vector.
   */
  Vector4 clone() const { return Vector4(x, y, z, w); }

  /**
   * Copies the components of the specified 4D vector to this 4D vector.
   *
   * @param source A 4D vector to copy the components from.
   * @returns This vector.
   */
  Vector4 &copy(const Vector4 &source) {
    x = source.x;
    y = source.y;
    z = source.z;
    w = source.w;

    return *this;
  }

  /**
   * Sets the components of this 4D vector.
   *
   * @param _x The new x component.
   * @param _y The new y component.
   * @param _z The new z component.
   * @param _w The new w component.
   * @returns This vector.
   */
  Vector4 &set(double _x, double _y, double _z, double _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;

    return *this;
  }

  /**
   * Returns the 3D vector represented by the x, y, and z components of this
   * 4D vector with perspective division.
   *
   * That is, if this 4D vector is \f$(x, y, z, w)\f$, then return the 3D vector
   * \f$(x/w, y/w, z/w)\f$.
   *
   * @returns The 3D vector represented by the x, y, and z components of this
   * 4D vector with perspective division.
   */
  Vector3 toVector3() const { return Vector3(x, y, z) / w; }

  /**
   * Returns the length of this 4D vector.
   *
   * Specifically, returns the [Euclidean
   * length](https://en.wikipedia.org/wiki/Euclidean_distance).
   *
   * @returns The length of this vector.
   */
  double length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

  /**
   * Returns the unit vector of this 4D vector.
   *
   * @returns The unit vector of this vector.
   */
  Vector4 unit() const { return *this / length(); }

  /**
   * Normalizes this 4D vector.
   *
   * Note that this method modifies this instance. If you want to avoid
   * modification, use {@link #unit} instead.
   *
   * @returns This vector.
   */
  Vector4 &normalize() {
    *this /= length();
    return *this;
  }

  /**
   * Returns a new 4D vector with the absolute values of the components of this
   * 4D vector.
   *
   * @returns A new vector with the absolute values of the components of this
   * vector.
   */
  Vector4 absolute() const {
    return Vector4(std::abs(x), std::abs(y), std::abs(z), std::abs(w));
  }

  /**
   * Sets the components of this 4D vector to their absolute values.
   *
   * Note that this method modifies this instance. If you want to avoid
   * modification, use {@link #absolute} instead.
   *
   * @returns This vector.
   */
  Vector4 &abs() {
    x = std::abs(x);
    y = std::abs(y);
    z = std::abs(z);
    w = std::abs(w);

    return *this;
  }

  /**
   * Clamps the components of this 4D vector to the specified minimum and
   * maximum 4D vectors component-wise.
   *
   * @param min The minimum 4D vector.
   * @param max The maximum 4D vector.
   * @returns This vector.
   */
  Vector4 &clamp(const Vector4 &min, const Vector4 &max) {
    x = std::clamp(x, min.x, max.x);
    y = std::clamp(y, min.y, max.y);
    z = std::clamp(z, min.z, max.z);
    w = std::clamp(w, min.w, max.w);

    return *this;
  }

  /**
   * Clamps the components of this 4D vector to the specified minimum and
   * maximum values.
   *
   * @param min The minimum value.
   * @param max The maximum value.
   * @returns This vector.
   */
  Vector4 &clamp(double min, double max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);
    w = std::clamp(w, min, max);

    return *this;
  }

  /**
   * Returns the component at the specified index of this 4D vector.
   *
   * @param index A 0-based index. Must be 0, 1, 2, or 3.
   * @returns The component at `index`.
   * @throws std::invalid_argument if `index` is not 0, 1, 2, or 3.
   */
  double operator[](std::size_t index) const {
    switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::invalid_argument("Index to Vector4 must be 0, 1, 2, or 3.");
    }
  }

  /**
   * Adds the specified 4D vector to this vector.
   *
   * @param v A 4D vector.
   * @returns This vector.
   */
  Vector4 &operator+=(const Vector4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
  }

  /**
   * Adds the specified constant to all components in this 4D vector.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector4 &operator+=(double s) {
    x += s;
    y += s;
    z += s;
    w += s;

    return *this;
  }

  /**
   * Subtracts the specified 4D vector from this vector.
   *
   * @param v A 4D vector.
   * @returns This vector.
   */
  Vector4 &operator-=(const Vector4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
  }

  /**
   * Subtracts the specified constant from all components in this 4D vector.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector4 &operator-=(double s) {
    x -= s;
    y -= s;
    z -= s;
    w -= s;

    return *this;
  }

  /**
   * Multiplies the components of this vector with the corresponding components
   * of the specified 4D vector.
   *
   * @param v A 4D vector.
   * @returns This vector.
   *
   * @see #dot
   * @see #cross
   */
  Vector4 &operator*=(const Vector4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;

    return *this;
  }

  /**
   * Multiplies all components of this 4D vector with the specified constant.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector4 &operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
  }

  /**
   * Divides the components of this vector by the corresponding components of
   * another 4D vector
   *
   * @param v A 4D vector.
   * @returns This vector.
   */
  Vector4 &operator/=(const Vector4 &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;

    return *this;
  }

  /**
   * Divides the components of this 4D vector by the specified constant.
   *
   * @param s A constant.
   * @returns This vector.
   */
  Vector4 &operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
  }

  /**
   * Returns the negation of this 4D vector.
   *
   * @returns The negation of this 4D vector.
   */
  friend Vector3 operator-(const Vector3 &a) { return a * -1; }

  /**
   * Adds two 4D vectors.
   *
   * @param a A 4D vector.
   * @param b Another 4D vector.
   * @returns The sum of `a` and `b`.
   */
  friend Vector4 operator+(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
  }

  /**
   * Adds a constant to all components of a 4D vector.
   *
   * @param a A 4D vector.
   * @param s A constant.
   * @returns The resulting vector when adding `s` to the components of `a`.
   */
  friend Vector4 operator+(const Vector4 &a, double s) {
    return Vector4(a.x + s, a.y + s, a.z + s, a.w + s);
  }

  /**
   * Adds a constant to all components of a 4D vector.
   *
   * @param s A constant.
   * @param a A 4D vector.
   * @returns The resulting vector when adding `s` to the components of `a`.
   */
  friend Vector4 operator+(double s, const Vector4 &a) { return a + s; }

  /**
   * Subtracts two 4D vectors.
   *
   * @param a A 4D vector.
   * @param b Another 4D vector.
   * @returns The difference of `a` and `b`.
   */
  friend Vector4 operator-(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
  }

  /**
   * Subtracts a constant from all components of a 4D vector.
   *
   * @param a A 4D vector.
   * @param s A constant.
   * @returns The resulting vector when subtracting `s` from the components of
   * `a`.
   */
  friend Vector4 operator-(const Vector4 &a, double s) {
    return Vector4(a.x - s, a.y - s, a.z - s, a.w - s);
  }

  /**
   * Subtracts a 4D vector from a constant 4D vector.
   *
   * A constant vector is a vector whose components are all the same.
   *
   * @param s A constant for the constant 4D vector.
   * @param a A 4D vector.
   * @returns The resulting vector when subtracting the components of `a` from
   * the constant vector of `s`.
   */
  friend Vector4 operator-(double s, const Vector4 &a) {
    return Vector4(s - a.x, s - a.y, s - a.z, s - a.w);
  }

  /**
   * Returns the element-wise product of two 4D vectors, also known as the
   * [Hadamard product](https://en.wikipedia.org/wiki/Hadamard_product_(matrices)).
   *
   * @param a A 4D vector.
   * @param b Another 4D vector.
   * @returns The element-wise product of `a` and `b`.
   */
  friend Vector4 operator*(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
  }

  /**
   * Multiplies all components of a 4D vector with a constant.
   *
   * @param a A 4D vector.
   * @param s A constant.
   * @returns The resulting vector when multiplying the components of `a` with
   * `s`.
   */
  friend Vector4 operator*(const Vector4 &a, double s) {
    return Vector4(a.x * s, a.y * s, a.z * s, a.w * s);
  }

  /**
   * Multiplies all components of a 4D vector with a constant.
   *
   * @param s A constant.
   * @param a A 4D vector.
   * @returns The resulting vector when multiplying the components of `a` with
   * `s`.
   */
  friend Vector4 operator*(double s, const Vector4 &a) { return a * s; }

  /**
   * Returns the element-wise division of two 4D vectors.
   *
   * @param a A 4D vector.
   * @param b Another 4D vector.
   * @returns The element-wise division `a` and `b`.
   */
  friend Vector4 operator/(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
  }

  /**
   * Divides the components of a 4D vector by a constant.
   *
   * @param a A 4D vector.
   * @param s A constant.
   * @returns The resulting vector when dividing the components of `a` by `s`.
   */
  friend Vector4 operator/(const Vector4 &a, double s) {
    return Vector4(a.x / s, a.y / s, a.z / s, a.w / s);
  }

  /**
   * Returns the element-wise division of a constant 4D vector and a 4D vector.
   *
   * A constant vector is a vector whose components are all the same.
   *
   * @param s A constant for the constant 4D vector.
   * @param a A 4D vector.
   * @returns The element-wise division of the constant 4D vector and `a`.
   */
  friend Vector4 operator/(double s, const Vector4 &a) {
    return Vector4(s / a.x, s / a.y, s / a.z, s / a.w);
  }
};

#undef m
#undef v

} // namespace t

#endif // VECTOR4_HPP