#include "primitives/BufferAttribute.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace t {

class Vector3 {
public:
  double x;
  double y;
  double z;

  static Vector3
  fromBufferAttribute(const BufferAttribute<double> &bufferAttribute,
                      int index) {
    return Vector3(
        bufferAttribute.array.at(index * bufferAttribute.itemSize),
        bufferAttribute.array.at(index * bufferAttribute.itemSize + 1),
        bufferAttribute.array.at(index * bufferAttribute.itemSize + 2));
  }

  static Vector3 cross(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x,
                   a.x * b.y - b.x * a.y);
  }

  static double dot(const Vector3 &a, const Vector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  static Vector3 reflect(const Vector3 &incident,
                         const Vector3 &surfaceOrientation) {
    return incident -
           2.0 * dot(surfaceOrientation, incident) * surfaceOrientation;
  }

  Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

  Vector3 clone() const { return Vector3(x, y, z); }

  Vector3 &copy(const Vector3 &source) {
    x = source.x;
    y = source.y;
    z = source.z;

    return *this;
  }

  Vector3 &set(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;

    return *this;
  }

  double length() const { return std::sqrt(x * x + y * y + z * z); }

  Vector3 unit() const { return *this / length(); }

  Vector3 &normalize() {
    *this /= length();
    return *this;
  }

  Vector3 absolute() const {
    return Vector3(std::abs(x), std::abs(y), std::abs(z));
  }

  Vector3 &abs() {
    x = std::abs(x);
    y = std::abs(y);
    z = std::abs(z);

    return *this;
  }

  Vector3 &clamp(const Vector3 &min, const Vector3 &max) {
    x = std::clamp(x, min.x, max.x);
    y = std::clamp(y, min.y, max.y);
    z = std::clamp(z, min.z, max.z);

    return *this;
  }

  Vector3 &clamp(double min, double max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);

    return *this;
  }

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

  Vector3 &operator+=(const Vector3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
  }

  Vector3 &operator+=(double s) {
    x += s;
    y += s;
    z += s;

    return *this;
  }

  Vector3 &operator-=(const Vector3 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
  }

  Vector3 &operator-=(double s) {
    x -= s;
    y -= s;
    z -= s;

    return *this;
  }

  Vector3 &operator*=(const Vector3 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;

    return *this;
  }

  Vector3 &operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;

    return *this;
  }

  Vector3 &operator/=(const Vector3 &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;

    return *this;
  }

  Vector3 &operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;

    return *this;
  }

  friend bool operator==(const Vector3 &a, const Vector3 &b) = default;

  friend Vector3 operator-(const Vector3 &a) { return a * -1; }

  friend Vector3 operator+(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  friend Vector3 operator+(const Vector3 &a, double s) {
    return Vector3(a.x + s, a.y + s, a.z + s);
  }

  friend Vector3 operator+(double s, const Vector3 &a) { return a + s; }

  friend Vector3 operator-(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
  }

  friend Vector3 operator-(const Vector3 &a, double s) {
    return Vector3(a.x - s, a.y - s, a.z - s);
  }

  friend Vector3 operator-(double s, const Vector3 &a) {
    return Vector3(s - a.x, s - a.y, s - a.z);
  }

  friend Vector3 operator*(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
  }

  friend Vector3 operator*(const Vector3 &a, double s) {
    return Vector3(a.x * s, a.y * s, a.z * s);
  }

  friend Vector3 operator*(double s, const Vector3 &a) { return a * s; }

  friend Vector3 operator/(const Vector3 &a, const Vector3 &b) {
    return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
  }

  friend Vector3 operator/(const Vector3 &a, double s) {
    return Vector3(a.x / s, a.y / s, a.z / s);
  }

  friend Vector3 operator/(double s, const Vector3 &a) {
    return Vector3(s / a.x, s / a.y, s / a.z);
  }
};

} // namespace t

#endif // VECTOR3_HPP