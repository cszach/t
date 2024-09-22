#include "math/Vector3.hpp"
#include <array>

#ifndef MATRIX3X3_HPP
#define MATRIX3X3_HPP

namespace t {

#define n11 elements[0]
#define n12 elements[1]
#define n13 elements[2]
#define n21 elements[3]
#define n22 elements[4]
#define n23 elements[5]
#define n31 elements[6]
#define n32 elements[7]
#define n33 elements[8]

class Matrix3x3 {
public:
  std::array<double, 9> elements;

  static Matrix3x3 identity() { return Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); }

  Matrix3x3(double _n11, double _n12, double _n13, double _n21, double _n22,
            double _n23, double _n31, double _n32, double _n33)
      : elements({_n11, _n12, _n13, _n21, _n22, _n23, _n31, _n32, _n33}) {}

  Matrix3x3 clone() const {
    return Matrix3x3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
  }

  Matrix3x3 &copy(const Matrix3x3 &source) {
    for (auto i = 0; i < 9; ++i) {
      elements[i] = source.elements[i];
    }

    return *this;
  }

  Matrix3x3 &set(double _n11, double _n12, double _n13, double _n21,
                 double _n22, double _n23, double _n31, double _n32,
                 double _n33) {
    n11 = _n11;
    n12 = _n12;
    n13 = _n13;
    n21 = _n21;
    n22 = _n22;
    n23 = _n23;
    n31 = _n31;
    n32 = _n32;
    n33 = _n33;

    return *this;
  }

  double get(int row, int column) const {
    return elements.at(row * 3 + column);
  }

  Matrix3x3 &set(int row, int column, int value) {
    elements.at(row * 3 + column) = value;
    return *this;
  }

  Matrix3x3 &reset() { return set(1, 0, 0, 0, 1, 0, 0, 0, 1); }

  double determinant() const {
    return n11 * n22 * n33 + n12 * n23 * n31 + n13 * n21 * n32 -
           n11 * n23 * n32 - n12 * n21 * n33 - n13 * n22 * n31;
  }

  Matrix3x3 transpose() const {
    return Matrix3x3(n11, n21, n31, n12, n22, n32, n13, n23, n33);
  }

  Matrix3x3 inverse() const {
    double det = determinant();

    if (det == 0) {
      return Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    return Matrix3x3(
        (n22 * n33 - n23 * n32) / det, (n13 * n32 - n12 * n33) / det,
        (n12 * n23 - n13 * n22) / det, (n23 * n31 - n21 * n33) / det,
        (n11 * n33 - n13 * n31) / det, (n13 * n21 - n11 * n23) / det,
        (n21 * n32 - n22 * n31) / det, (n12 * n31 - n11 * n32) / det,
        (n11 * n22 - n12 * n21) / det);
  }

  double operator[](std::size_t index) const { return elements[index]; }

  Matrix3x3 &operator+=(const Matrix3x3 &m) {
    for (int i = 0; i < 9; ++i) {
      elements[i] += m.elements[i];
    }

    return *this;
  }

  Matrix3x3 &operator+=(double s) {
    for (auto &element : elements) {
      element += s;
    }

    return *this;
  }

  Matrix3x3 &operator-=(const Matrix3x3 &m) {
    for (int i = 0; i < 9; ++i) {
      elements[i] -= m.elements[i];
    }

    return *this;
  }

  Matrix3x3 &operator-=(double s) {
    for (auto &element : elements) {
      element -= s;
    }

    return *this;

    return *this;
  }

  Matrix3x3 &operator*=(const Matrix3x3 &m) { return this->copy(*this * m); }

  Matrix3x3 &operator*=(double s) {
    for (auto &element : elements) {
      element *= s;
    }

    return *this;
  }

  Matrix3x3 &operator/=(const Matrix3x3 &m) {
    for (int i = 0; i < 9; ++i) {
      elements[i] /= m[i];
    }

    return *this;
  }

  Matrix3x3 &operator/=(double s) {
    for (auto &element : elements) {
      element /= s;
    }

    return *this;
  }

  friend bool operator==(const Matrix3x3 &a, const Matrix3x3 &b) = default;

  friend Matrix3x3 operator+(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 + b.n11, a.n12 + b.n12, a.n13 + b.n13, a.n21 + b.n21,
                     a.n22 + b.n22, a.n23 + b.n23, a.n31 + b.n31, a.n32 + b.n32,
                     a.n33 + b.n33);
  }

  friend Matrix3x3 operator+(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 + s, a.n12 + s, a.n13 + s, a.n21 + s, a.n22 + s,
                     a.n23 + s, a.n31 + s, a.n32 + s, a.n33 + s);
  }

  friend Matrix3x3 operator+(double s, const Matrix3x3 &a) { return a + s; }

  friend Matrix3x3 operator-(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 - b.n11, a.n12 - b.n12, a.n13 - b.n13, a.n21 - b.n21,
                     a.n22 - b.n22, a.n23 - b.n23, a.n31 - b.n31, a.n32 - b.n32,
                     a.n33 - b.n33);
  }

  friend Matrix3x3 operator-(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 - s, a.n12 - s, a.n13 - s, a.n21 - s, a.n22 - s,
                     a.n23 - s, a.n31 - s, a.n32 - s, a.n33 - s);
  }

  friend Matrix3x3 operator-(double s, const Matrix3x3 &a) {
    return Matrix3x3(s - a.n11, s - a.n12, s - a.n13, s - a.n21, s - a.n22,
                     s - a.n23, s - a.n31, s - a.n32, s - a.n33);
  }

  friend Matrix3x3 operator*(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 * b.n11 + a.n12 * b.n21 + a.n13 * b.n31,
                     a.n11 * b.n12 + a.n12 * b.n22 + a.n13 * b.n32,
                     a.n11 * b.n13 + a.n12 * b.n23 + a.n13 * b.n33,
                     a.n21 * b.n11 + a.n22 * b.n21 + a.n23 * b.n31,
                     a.n21 * b.n12 + a.n22 * b.n22 + a.n23 * b.n32,
                     a.n21 * b.n13 + a.n22 * b.n23 + a.n23 * b.n33,
                     a.n31 * b.n11 + a.n32 * b.n21 + a.n33 * b.n31,
                     a.n31 * b.n12 + a.n32 * b.n22 + a.n33 * b.n32,
                     a.n31 * b.n13 + a.n32 * b.n23 + a.n33 * b.n33);
  }

  friend Matrix3x3 operator*(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 * s, a.n12 * s, a.n13 * s, a.n21 * s, a.n22 * s,
                     a.n23 * s, a.n31 * s, a.n32 * s, a.n33 * s);
  }

  friend Matrix3x3 operator*(double s, const Matrix3x3 &a) { return a * s; }

  friend Vector3 operator*(const Matrix3x3 &a, const Vector3 &v) {
    return Vector3(a.n11 * v.x + a.n12 * v.y + a.n13 * v.z,
                   a.n21 * v.x + a.n22 * v.y + a.n23 * v.z,
                   a.n31 * v.x + a.n32 * v.y + a.n33 * v.z);
  }

  friend Matrix3x3 operator/(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 / b.n11, a.n12 / b.n12, a.n13 / b.n13, a.n21 / b.n21,
                     a.n22 / b.n22, a.n23 / b.n23, a.n31 / b.n31, a.n32 / b.n32,
                     a.n33 / b.n33);
  }

  friend Matrix3x3 operator/(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 / s, a.n12 / s, a.n13 / s, a.n21 / s, a.n22 / s,
                     a.n23 / s, a.n31 / s, a.n32 / s, a.n33 / s);
  }

  friend Matrix3x3 operator/(double s, const Matrix3x3 &a) {
    return Matrix3x3(s / a.n11, s / a.n12, s / a.n13, s / a.n21, s / a.n22,
                     s / a.n23, s / a.n31, s / a.n32, s / a.n33);
  }
};

#undef n11
#undef n12
#undef n13
#undef n21
#undef n22
#undef n23
#undef n31
#undef n32
#undef n33

} // namespace t

#endif // MATRIX3X3_HPP