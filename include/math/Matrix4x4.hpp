#include "EulerRotation.hpp"
#include "Matrix3x3.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include <array>
#include <cmath>

#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

namespace t {

#define n11 elements[0]
#define n12 elements[1]
#define n13 elements[2]
#define n14 elements[3]
#define n21 elements[4]
#define n22 elements[5]
#define n23 elements[6]
#define n24 elements[7]
#define n31 elements[8]
#define n32 elements[9]
#define n33 elements[10]
#define n34 elements[11]
#define n41 elements[12]
#define n42 elements[13]
#define n43 elements[14]
#define n44 elements[15]

class Matrix4x4 {
public:
  std::array<double, 16> elements;

  static Matrix4x4 identity() {
    // clang-format off
    return Matrix4x4(1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1);
    // clang-format on
  }

  static Matrix4x4 zero() {
    // clang-format off
    return Matrix4x4(0, 0, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0);
    // clang-format on
  }

  static Matrix4x4 fromTranslation(const Vector3 &distance) {
    // clang-format off
    return Matrix4x4(1, 0, 0, distance.x,
                     0, 1, 0, distance.y,
                     0, 0, 1, distance.z,
                     0, 0, 0,          1);
    // clang-format on
  }

  static Matrix4x4 fromRotation(const EulerRotation &angle) {
    // clang-format off
    auto rotationX = Matrix4x4(1,                 0,                  0, 0,
                               0, std::cos(angle.x), -std::sin(angle.x), 0,
                               0, std::sin(angle.x),  std::cos(angle.x), 0,
                               0,                 0,                  0, 1);
    // clang-format on

    // clang-format off
    auto rotationY = Matrix4x4(std::cos(angle.y), 0, std::sin(angle.y), 0,
                                               0, 1,                 0, 0,
                              -std::sin(angle.y), 0, std::cos(angle.y), 0,
                                               0, 0,                 0, 1);
    // clang-format on

    // clang-format off
    auto rotationZ = Matrix4x4(std::cos(angle.z), -std::sin(angle.z), 0, 0,
                               std::sin(angle.z),  std::cos(angle.z), 0, 0,
                                               0,                  0, 1, 0,
                                               0,                  0, 0, 1);
    // clang-format on

    auto const &firstRotation =
        getRotationMatrix(rotationX, rotationY, rotationZ, angle.order, 0);
    auto const &secondRotation =
        getRotationMatrix(rotationX, rotationY, rotationZ, angle.order, 1);
    auto const &thirdRotation =
        getRotationMatrix(rotationX, rotationY, rotationZ, angle.order, 2);

    return thirdRotation * secondRotation * firstRotation;
  }

  static Matrix4x4 fromScale(const Vector3 &scaleFactor) {
    // clang-format off
    return Matrix4x4(scaleFactor.x,             0,             0, 0,
                                 0, scaleFactor.y,             0, 0,
                                 0,             0, scaleFactor.z, 0,
                                 0,             0,             0, 1);
    // clang-format on
  }

  Matrix4x4(double _n11, double _n12, double _n13, double _n14, double _n21,
            double _n22, double _n23, double _n24, double _n31, double _n32,
            double _n33, double _n34, double _n41, double _n42, double _n43,
            double _n44)
      : elements({_n11, _n12, _n13, _n14, _n21, _n22, _n23, _n24, _n31, _n32,
                  _n33, _n34, _n41, _n42, _n43, _n44}) {}

  Matrix4x4 clone() const {
    // clang-format off
    return Matrix4x4(n11, n12, n13, n14,
                     n21, n22, n23, n24,
                     n31, n32, n33, n34,
                     n41, n42, n43, n44);
    // clang-format on
  }

  Matrix4x4 &copy(const Matrix4x4 &source) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] = source.elements[i];
    }

    return *this;
  }

  Matrix4x4 &set(double _n11, double _n12, double _n13, double _n14,
                 double _n21, double _n22, double _n23, double _n24,
                 double _n31, double _n32, double _n33, double _n34,
                 double _n41, double _n42, double _n43, double _n44) {
    n11 = _n11;
    n12 = _n12;
    n13 = _n13;
    n14 = _n14;
    n21 = _n21;
    n22 = _n22;
    n23 = _n23;
    n24 = _n24;
    n31 = _n31;
    n32 = _n32;
    n33 = _n33;
    n34 = _n34;
    n41 = _n41;
    n42 = _n42;
    n43 = _n43;
    n44 = _n44;

    return *this;
  }

  double get(int row, int column) const {
    return elements.at(row * 4 + column);
  }

  Matrix4x4 &set(int row, int column, int value) {
    elements.at(row * 4 + column) = value;
    return *this;
  }

  Matrix4x4 &reset() {
    // clang-format off
    return set(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               0, 0, 0, 1);
    // clang-format on
  }

  double determinant() const {
    // clang-format off
    return
      n14 * n23 * n32 * n41 - n13 * n24 * n32 * n41 - n14 * n22 * n33 * n41 + n12 * n24 * n33 * n41 +
      n13 * n22 * n34 * n41 - n12 * n23 * n34 * n41 - n14 * n23 * n31 * n42 + n13 * n24 * n31 * n42 +
      n14 * n21 * n33 * n42 - n11 * n24 * n33 * n42 - n13 * n21 * n34 * n42 + n11 * n23 * n34 * n42 +
      n14 * n22 * n31 * n43 - n12 * n24 * n31 * n43 - n14 * n21 * n32 * n43 + n11 * n24 * n32 * n43 +
      n12 * n21 * n34 * n43 - n11 * n22 * n34 * n43 - n13 * n22 * n31 * n44 + n12 * n23 * n31 * n44 +
      n13 * n21 * n32 * n44 - n11 * n23 * n32 * n44 - n12 * n21 * n33 * n44 + n11 * n22 * n33 * n44;
    // clang-format on
  }

  Matrix4x4 transpose() const {
    // clang-format off
    return Matrix4x4(n11, n21, n31, n41,
                     n12, n22, n32, n42,
                     n13, n23, n33, n43,
                     n14, n24, n34, n44);
    // clang-format on
  }

  Matrix4x4 inverse() const {
    auto det = determinant();

    if (det == 0) {
      return Matrix4x4::zero();
    }

    // clang-format off
    auto adjoint = Matrix4x4(
      n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44,
      n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44,
      n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44,
      n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34,
      n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44,
      n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44,
      n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44,
      n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34,
      n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44,
      n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44,
      n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44,
      n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34,
      n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43,
      n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43,
      n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43,
      n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33
    );
    // clang-format on

    return (1.0 / det) * adjoint;
  }

  Matrix3x3 topLeft3x3Matrix() const {
    return Matrix3x3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
  }

  double operator[](std::size_t index) const { return elements.at(index); }

  Matrix4x4 &operator+=(const Matrix4x4 &m) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] += m.elements[i];
    }

    return *this;
  }

  Matrix4x4 &operator+=(double s) {
    for (auto &element : elements) {
      element += s;
    }

    return *this;
  }

  Matrix4x4 &operator-=(const Matrix4x4 &m) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] -= m.elements[i];
    }

    return *this;
  }

  Matrix4x4 &operator-=(double s) {
    for (auto &element : elements) {
      element -= s;
    }

    return *this;
  }

  Matrix4x4 &operator*=(const Matrix4x4 &m) { return this->copy(*this * m); }

  Matrix4x4 &operator*=(double s) {
    for (auto &element : elements) {
      element *= s;
    }

    return *this;
  }

  Matrix4x4 &operator/=(const Matrix4x4 &m) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] /= m.elements[i];
    }

    return *this;
  }

  Matrix4x4 &operator/=(double s) {
    for (auto &element : elements) {
      element /= s;
    }

    return *this;
  }

  friend bool operator==(const Matrix4x4 &a, const Matrix4x4 &b) = default;

  friend Matrix4x4 operator+(const Matrix4x4 &a, const Matrix4x4 &b) {
    // clang-format off
    return Matrix4x4(a.n11 + b.n11, a.n12 + b.n12, a.n13 + b.n13, a.n14 + b.n14,
                     a.n21 + b.n21, a.n22 + b.n22, a.n23 + b.n23, a.n24 + b.n24,
                     a.n31 + b.n31, a.n32 + b.n32, a.n33 + b.n33, a.n34 + b.n34,
                     a.n41 + b.n41, a.n42 + b.n42, a.n43 + b.n43, a.n44 + b.n44);
    // clang-format on
  }

  friend Matrix4x4 operator+(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 + s, a.n12 + s, a.n13 + s, a.n14 + s,
                     a.n21 + s, a.n22 + s, a.n23 + s, a.n24 + s,
                     a.n31 + s, a.n32 + s, a.n33 + s, a.n34 + s,
                     a.n41 + s, a.n42 + s, a.n43 + s, a.n44 + s);
    // clang-format on
  }

  friend Matrix4x4 operator+(double s, const Matrix4x4 &a) { return a + s; }

  friend Matrix4x4 operator-(const Matrix4x4 &a, const Matrix4x4 &b) {
    // clang-format off
    return Matrix4x4(a.n11 - b.n11, a.n12 - b.n12, a.n13 - b.n13, a.n14 - b.n14,
                     a.n21 - b.n21, a.n22 - b.n22, a.n23 - b.n23, a.n24 - b.n24,
                     a.n31 - b.n31, a.n32 - b.n32, a.n33 - b.n33, a.n34 - b.n34,
                     a.n41 - b.n41, a.n42 - b.n42, a.n43 - b.n43, a.n44 - b.n44);
    // clang-format on
  }

  friend Matrix4x4 operator-(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 - s, a.n12 - s, a.n13 - s, a.n14 - s,
                     a.n21 - s, a.n22 - s, a.n23 - s, a.n24 - s,
                     a.n31 - s, a.n32 - s, a.n33 - s, a.n34 - s,
                     a.n41 - s, a.n42 - s, a.n43 - s, a.n44 - s);
    // clang-format on
  }

  friend Matrix4x4 operator-(double s, const Matrix4x4 &a) {
    // clang-format off
    return Matrix4x4(s - a.n11, s - a.n12, s - a.n13, s - a.n14,
                     s - a.n21, s - a.n22, s - a.n23, s - a.n24,
                     s - a.n31, s - a.n32, s - a.n33, s - a.n34,
                     s - a.n41, s - a.n42, s - a.n43, s - a.n44);
    // clang-format on
  }

  friend Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &b) {
    return Matrix4x4(
        a.n11 * b.n11 + a.n12 * b.n21 + a.n13 * b.n31 + a.n14 * b.n41,
        a.n11 * b.n12 + a.n12 * b.n22 + a.n13 * b.n32 + a.n14 * b.n42,
        a.n11 * b.n13 + a.n12 * b.n23 + a.n13 * b.n33 + a.n14 * b.n43,
        a.n11 * b.n14 + a.n12 * b.n24 + a.n13 * b.n34 + a.n14 * b.n44,
        a.n21 * b.n11 + a.n22 * b.n21 + a.n23 * b.n31 + a.n24 * b.n41,
        a.n21 * b.n12 + a.n22 * b.n22 + a.n23 * b.n32 + a.n24 * b.n42,
        a.n21 * b.n13 + a.n22 * b.n23 + a.n23 * b.n33 + a.n24 * b.n43,
        a.n21 * b.n14 + a.n22 * b.n24 + a.n23 * b.n34 + a.n24 * b.n44,
        a.n31 * b.n11 + a.n32 * b.n21 + a.n33 * b.n31 + a.n34 * b.n41,
        a.n31 * b.n12 + a.n32 * b.n22 + a.n33 * b.n32 + a.n34 * b.n42,
        a.n31 * b.n13 + a.n32 * b.n23 + a.n33 * b.n33 + a.n34 * b.n43,
        a.n31 * b.n14 + a.n32 * b.n24 + a.n33 * b.n34 + a.n34 * b.n44,
        a.n41 * b.n11 + a.n42 * b.n21 + a.n43 * b.n31 + a.n44 * b.n41,
        a.n41 * b.n12 + a.n42 * b.n22 + a.n43 * b.n32 + a.n44 * b.n42,
        a.n41 * b.n13 + a.n42 * b.n23 + a.n43 * b.n33 + a.n44 * b.n43,
        a.n41 * b.n14 + a.n42 * b.n24 + a.n43 * b.n34 + a.n44 * b.n44);
  }

  friend Matrix4x4 operator*(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 * s, a.n12 * s, a.n13 * s, a.n14 * s,
                     a.n21 * s, a.n22 * s, a.n23 * s, a.n24 * s,
                     a.n31 * s, a.n32 * s, a.n33 * s, a.n34 * s,
                     a.n41 * s, a.n42 * s, a.n43 * s, a.n44 * s);
    // clang-format on
  }

  friend Matrix4x4 operator*(double s, const Matrix4x4 &a) { return a * s; }

  friend Vector4 operator*(const Matrix4x4 &a, const Vector4 &v) {
    return Vector4(a.n11 * v.x + a.n12 * v.y + a.n13 * v.z + a.n14 * v.w,
                   a.n21 * v.x + a.n22 * v.y + a.n23 * v.z + a.n24 * v.w,
                   a.n31 * v.x + a.n32 * v.y + a.n33 * v.z + a.n34 * v.w,
                   a.n41 * v.x + a.n42 * v.y + a.n43 * v.z + a.n44 * v.w);
  }

  friend Matrix4x4 operator/(const Matrix4x4 &a, const Matrix4x4 &b) {
    // clang-format off
    return Matrix4x4(a.n11 / b.n11, a.n12 / b.n12, a.n13 / b.n13, a.n14 / b.n14,
                     a.n21 / b.n21, a.n22 / b.n22, a.n23 / b.n23, a.n24 / b.n24,
                     a.n31 / b.n31, a.n32 / b.n32, a.n33 / b.n33, a.n34 / b.n34,
                     a.n41 / b.n41, a.n42 / b.n42, a.n43 / b.n43, a.n44 / b.n44);
    // clang-format on
  }

  friend Matrix4x4 operator/(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 / s, a.n12 / s, a.n13 / s, a.n14 / s,
                     a.n21 / s, a.n22 / s, a.n23 / s, a.n24 / s,
                     a.n31 / s, a.n32 / s, a.n33 / s, a.n34 / s,
                     a.n41 / s, a.n42 / s, a.n43 / s, a.n44 / s);
    // clang-format on
  }

  friend Matrix4x4 operator/(double s, const Matrix4x4 &a) {
    // clang-format off
    return Matrix4x4(s / a.n11, s / a.n12, s / a.n13, s / a.n14,
                     s / a.n21, s / a.n22, s / a.n23, s / a.n24,
                     s / a.n31, s / a.n32, s / a.n33, s / a.n34,
                     s / a.n41, s / a.n42, s / a.n43, s / a.n44);
    // clang-format on
  }

private:
  static Matrix4x4 &getRotationMatrix(Matrix4x4 &rotationX,
                                      Matrix4x4 &rotationY,
                                      Matrix4x4 &rotationZ,
                                      EulerRotationOrder order, int index) {
    switch (index) {
      using enum EulerRotationOrder;
    case 0:
      switch (order) {
      case Xyz:
      case Xzy:
        return rotationX;

      case Yxz:
      case Yzx:
        return rotationY;

      case Zxy:
      case Zyx:
        return rotationZ;
      }

    case 1:
      switch (order) {
      case Yxz:
      case Zxy:
        return rotationX;

      case Xyz:
      case Zyx:
        return rotationY;

      case Xzy:
      case Yzx:
        return rotationZ;
      }

    case 2:
      switch (order) {
      case Yzx:
      case Zyx:
        return rotationX;

      case Xzy:
      case Zxy:
        return rotationY;

      case Xyz:
      case Yxz:
        return rotationZ;
      }

    default:
      return rotationX;
    }
  }
};

#undef n11
#undef n12
#undef n13
#undef n14
#undef n21
#undef n22
#undef n23
#undef n24
#undef n31
#undef n32
#undef n33
#undef n34
#undef n41
#undef n42
#undef n43
#undef n44

} // namespace t

#endif // MATRIX4X4_HPP