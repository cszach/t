#include "math/Vector3.hpp"

#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace t {

#define m matrix4.elements
#define v vector4

class Vector4 {
public:
  double x;
  double y;
  double z;
  double w;

  Vector4(double _x, double _y, double _z, double _w)
      : x(_x), y(_y), z(_z), w(_w) {}

  Vector4(const Vector3 &vector3, double w)
      : Vector4(vector3.x, vector3.y, vector3.z, w) {}

  Vector4 clone() const { return Vector4(x, y, z, w); }

  Vector4 &copy(const Vector4 &source) {
    x = source.x;
    y = source.y;
    z = source.z;
    w = source.w;

    return *this;
  }

  Vector4 &set(double _x, double _y, double _z, double _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;

    return *this;
  }

  Vector3 toVector3() const { return Vector3(x, y, z) / w; }

  double length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

  Vector4 unit() const { return *this / length(); }

  Vector4 &normalize() {
    *this /= length();
    return *this;
  }

  Vector4 absolute() const {
    return Vector4(std::abs(x), std::abs(y), std::abs(z), std::abs(w));
  }

  Vector4 &abs() {
    x = std::abs(x);
    y = std::abs(y);
    z = std::abs(z);
    w = std::abs(w);

    return *this;
  }

  Vector4 &clamp(const Vector4 &min, const Vector4 &max) {
    x = std::clamp(x, min.x, max.x);
    y = std::clamp(y, min.y, max.y);
    z = std::clamp(z, min.z, max.z);
    w = std::clamp(w, min.w, max.w);

    return *this;
  }

  Vector4 &clamp(double min, double max) {
    x = std::clamp(x, min, max);
    y = std::clamp(y, min, max);
    z = std::clamp(z, min, max);
    w = std::clamp(w, min, max);

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
    case 3:
      return w;
    default:
      throw std::invalid_argument("Index to Vector4 must be 0, 1, 2, or 3.");
    }
  }

  Vector4 &operator+=(const Vector4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
  }

  Vector4 &operator+=(double s) {
    x += s;
    y += s;
    z += s;
    w += s;

    return *this;
  }

  Vector4 &operator-=(const Vector4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
  }

  Vector4 &operator-=(double s) {
    x -= s;
    y -= s;
    z -= s;
    w -= s;

    return *this;
  }

  Vector4 &operator*=(const Vector4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;

    return *this;
  }

  Vector4 &operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
  }

  Vector4 &operator/=(const Vector4 &v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;

    return *this;
  }

  Vector4 &operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
  }

  friend bool operator==(const Vector4 &a, const Vector4 &b) = default;

  friend Vector4 operator+(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
  }

  friend Vector4 operator+(const Vector4 &a, double s) {
    return Vector4(a.x + s, a.y + s, a.z + s, a.w + s);
  }

  friend Vector4 operator+(double s, const Vector4 &a) { return a + s; }

  friend Vector4 operator-(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
  }

  friend Vector4 operator-(const Vector4 &a, double s) {
    return Vector4(a.x - s, a.y - s, a.z - s, a.w - s);
  }

  friend Vector4 operator-(double s, const Vector4 &a) {
    return Vector4(s - a.x, s - a.y, s - a.z, s - a.w);
  }

  friend Vector4 operator*(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
  }

  friend Vector4 operator*(const Vector4 &a, double s) {
    return Vector4(a.x * s, a.y * s, a.z * s, a.w * s);
  }

  friend Vector4 operator*(double s, const Vector4 &a) { return a * s; }

  friend Vector4 operator/(const Vector4 &a, const Vector4 &b) {
    return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
  }

  friend Vector4 operator/(const Vector4 &a, double s) {
    return Vector4(a.x / s, a.y / s, a.z / s, a.w / s);
  }

  friend Vector4 operator/(double s, const Vector4 &a) {
    return Vector4(s / a.x, s / a.y, s / a.z, s / a.w);
  }
};

#undef m
#undef v

} // namespace t

#endif // VECTOR4_HPP