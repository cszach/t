#define _USE_MATH_DEFINES
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

/**
 * The \f$4 \times 4\f$ matrix class.
 *
 * \ingroup math
 */
class Matrix4x4 {
public:
  std::array<double, 16> elements; /**< The array containing the elements of
                                      this matrix in row-major order. */

  /**
   * Returns a \f$4 \times 4\f$ identity matrix.
   *
   * @returns A \f$4 \times 4\f$ identity matrix.
   */
  static Matrix4x4 identity() {
    // clang-format off
    return Matrix4x4(1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1);
    // clang-format on
  }

  /**
   * Returns a \f$4 \times 4\f$ zero matrix.
   *
   * @returns A \f$4 \times 4\f$ zero matrix.
   */
  static Matrix4x4 zero() {
    // clang-format off
    return Matrix4x4(0, 0, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0);
    // clang-format on
  }

  /**
   * Returns a translation matrix for the specified translation for
   * post-multiplication (\f$V' = AV\f$ where \f$V\f$ is the homogeneous
   * coordinates and \f$A\f$ is the transformation matrix).
   *
   * If you want to use pre-multiplication i.e. \f$V' = VA\f$, transpose the
   * returned matrix.
   *
   * @param distance The distance to translate along the x, y, and z axes.
   * @returns The translation matrix for `distance`.
   */
  static Matrix4x4 fromTranslation(const Vector3 &distance) {
    // clang-format off
    return Matrix4x4(1, 0, 0, distance.x,
                     0, 1, 0, distance.y,
                     0, 0, 1, distance.z,
                     0, 0, 0,          1);
    // clang-format on
  }

  /**
   * Returns a rotation matrix for the specified rotation for
   * post-multiplication (\f$V' = AV\f$ where \f$V\f$ is the homogeneous
   * coordinates and \f$A\f$ is the transformation matrix).
   *
   * If you want to use pre-multiplication i.e. \f$V' = VA\f$, transpose the
   * returned matrix.
   *
   * @param angle An Euler rotation.
   * @returns The rotation matrix for `angle`.
   */
  static Matrix4x4 fromRotation(const EulerRotation &angle) {
    // clang-format off
    auto rotationX = Matrix4x4(1,                 0,                  0, 0,
                               0, std::cos(angle.x), -std::sin(angle.x), 0,
                               0, std::sin(angle.x),  std::cos(angle.x), 0,
                               0,                 0,                  0, 1);

    auto rotationY = Matrix4x4(std::cos(angle.y), 0, std::sin(angle.y), 0,
                                               0, 1,                 0, 0,
                              -std::sin(angle.y), 0, std::cos(angle.y), 0,
                                               0, 0,                 0, 1);

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

  /**
   * Returns a scale matrix for the specified scale factor.
   *
   * @param scaleFactor The scale factor along the x, y, and z axes.
   * @returns The scale matrix for `scaleFactor`.
   */
  static Matrix4x4 fromScale(const Vector3 &scaleFactor) {
    // clang-format off
    return Matrix4x4(scaleFactor.x,             0,             0, 0,
                                 0, scaleFactor.y,             0, 0,
                                 0,             0, scaleFactor.z, 0,
                                 0,             0,             0, 1);
    // clang-format on
  }

  /**
   * Creates a new \f$4 \times 4\f$ matrix with the specified elements.
   *
   * @param _n11 The \f$(1, 1)\f$ element of the new matrix.
   * @param _n12 The \f$(1, 2)\f$ element of the new matrix.
   * @param _n13 The \f$(1, 3)\f$ element of the new matrix.
   * @param _n14 The \f$(1, 4)\f$ element of the new matrix.
   * @param _n21 The \f$(2, 1)\f$ element of the new matrix.
   * @param _n22 The \f$(2, 2)\f$ element of the new matrix.
   * @param _n23 The \f$(2, 3)\f$ element of the new matrix.
   * @param _n24 The \f$(2, 4)\f$ element of the new matrix.
   * @param _n31 The \f$(3, 1)\f$ element of the new matrix.
   * @param _n32 The \f$(3, 2)\f$ element of the new matrix.
   * @param _n33 The \f$(3, 3)\f$ element of the new matrix.
   * @param _n34 The \f$(3, 4)\f$ element of the new matrix.
   * @param _n41 The \f$(4, 1)\f$ element of the new matrix.
   * @param _n42 The \f$(4, 2)\f$ element of the new matrix.
   * @param _n43 The \f$(4, 3)\f$ element of the new matrix.
   * @param _n44 The \f$(4, 4)\f$ element of the new matrix.
   */
  Matrix4x4(double _n11, double _n12, double _n13, double _n14, double _n21,
            double _n22, double _n23, double _n24, double _n31, double _n32,
            double _n33, double _n34, double _n41, double _n42, double _n43,
            double _n44)
      : elements({_n11, _n12, _n13, _n14, _n21, _n22, _n23, _n24, _n31, _n32,
                  _n33, _n34, _n41, _n42, _n43, _n44}) {}

  /**
   * Returns a copy of this matrix.
   *
   * @returns A copy of this matrix.
   */
  Matrix4x4 clone() const {
    // clang-format off
    return Matrix4x4(n11, n12, n13, n14,
                     n21, n22, n23, n24,
                     n31, n32, n33, n34,
                     n41, n42, n43, n44);
    // clang-format on
  }

  /**
   * Copies the elements of another \f$4 \times 4\f$ matrix into this matrix.
   *
   * @param source The \f$4 \times 4\f$ matrix to copy from.
   * @returns This matrix.
   */
  Matrix4x4 &copy(const Matrix4x4 &source) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] = source.elements[i];
    }

    return *this;
  }

  /**
   * Sets the elements of this matrix.
   *
   * @param _n11 The new \f$(1, 1)\f$ element of this matrix.
   * @param _n12 The new \f$(1, 2)\f$ element of this matrix.
   * @param _n13 The new \f$(1, 3)\f$ element of this matrix.
   * @param _n14 The new \f$(1, 4)\f$ element of this matrix.
   * @param _n21 The new \f$(2, 1)\f$ element of this matrix.
   * @param _n22 The new \f$(2, 2)\f$ element of this matrix.
   * @param _n23 The new \f$(2, 3)\f$ element of this matrix.
   * @param _n24 The new \f$(2, 4)\f$ element of this matrix.
   * @param _n31 The new \f$(3, 1)\f$ element of this matrix.
   * @param _n32 The new \f$(3, 2)\f$ element of this matrix.
   * @param _n33 The new \f$(3, 3)\f$ element of this matrix.
   * @param _n34 The new \f$(3, 4)\f$ element of this matrix.
   * @param _n41 The new \f$(4, 1)\f$ element of this matrix.
   * @param _n42 The new \f$(4, 2)\f$ element of this matrix.
   * @param _n43 The new \f$(4, 3)\f$ element of this matrix.
   * @param _n44 The new \f$(4, 4)\f$ element of this matrix.
   * @returns This matrix.
   */
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

  /**
   * Gets the element at the specified row and column of this matrix with bounds
   * checking.
   *
   * @param row The 0-based index of the row of the element.
   * @param column The 0-based index of the column of the element.
   * @returns The element at the specified row and column of this matrix.
   *
   * @see {@link #operator[]} for accessing without bounds checking.
   */
  double get(int row, int column) const {
    return elements.at(row * 4 + column);
  }

  /**
   * Sets the element at the specified row and column of this matrix to the
   * specified value.
   *
   * @param row The 0-based index of the row of the element.
   * @param column The 0-based index of the column of the element.
   * @param value The new value for the element.
   * @returns This matrix.
   */
  Matrix4x4 &set(int row, int column, int value) {
    elements.at(row * 4 + column) = value;
    return *this;
  }

  /**
   * Resets this matrix to the \f$4 \times 4\f$ identity matrix.
   *
   * @returns This matrix.
   */
  Matrix4x4 &reset() {
    // clang-format off
    return set(1, 0, 0, 0,
               0, 1, 0, 0,
               0, 0, 1, 0,
               0, 0, 0, 1);
    // clang-format on
  }

  /**
   * Returns the [determinant](https://en.wikipedia.org/wiki/Determinant) of
   * this matrix.
   *
   * @returns The determinant of this matrix.
   */
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

  /**
   * Returns the [transpose](https://en.wikipedia.org/wiki/Transpose) of this
   * matrix.
   *
   * Note that this method does not modify this instance.
   *
   * @returns The transpose of this matrix.
   */
  Matrix4x4 transpose() const {
    // clang-format off
    return Matrix4x4(n11, n21, n31, n41,
                     n12, n22, n32, n42,
                     n13, n23, n33, n43,
                     n14, n24, n34, n44);
    // clang-format on
  }

  /**
   * Returns the inverse of this matrix or the zero matrix if this matrix does
   * not have an inverse.
   *
   * The inverse of a matrix \f$A\f$ is the matrix \f$A^{-1}\f$ such that
   * \f$AA^{-1} = I\f$ where \f$I\f$ is the identity matrix. A matrix does not
   * have an inverse if its determinant is zero.
   *
   * Note that this method does not modify this instance.
   *
   * @returns The inverse of this matrix.
   */
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

  /**
   * Returns the top-left \f$3 \times 3\f$ matrix of this matrix.
   *
   * For a transformation matrix, this method may be used to extract the
   * rotation and scale components of the transformation, while discarding the
   * translation component.
   *
   * @returns The top-left \f$3 \times 3\f$ matrix of this matrix.
   */
  Matrix3x3 topLeft3x3Matrix() const {
    return Matrix3x3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
  }

  /**
   * Returns the element at the specified index of this matrix without bounds
   * checking and assuming row-major ordering.
   *
   * The element at row \f$i\f$ and column \f$j\f$ of this matrix has the index
   * \f$4i + j\f$ assuming \f$i\f$ and \f$j\f$ are zero-based.
   *
   * @param index The 0-based index of the element in row-major order.
   * @returns The element at the specified index of this matrix.
   *
   * @see {@link #get} for accessing with bounds checking.
   */
  double operator[](std::size_t index) const { return elements.at(index); }

  /**
   * Adds the specified \f$4 \times 4\f$ matrix to this matrix.
   *
   * @param m A \f$4 \times 4\f$ matrix.
   * @returns This matrix.
   */
  Matrix4x4 &operator+=(const Matrix4x4 &m) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] += m.elements[i];
    }

    return *this;
  }

  /**
   * Adds the specified constant to all elements in this matrix.
   *
   * @param s A constant.
   * @returns This matrix.
   */
  Matrix4x4 &operator+=(double s) {
    for (auto &element : elements) {
      element += s;
    }

    return *this;
  }

  /**
   * Substracts the specified \f$4 \times 4\f$ matrix from this matrix.
   *
   * @param m A \f$4 \times 4\f$ matrix.
   * @returns This matrix.
   */
  Matrix4x4 &operator-=(const Matrix4x4 &m) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] -= m.elements[i];
    }

    return *this;
  }

  /**
   * Substracts the specified constant from all elements in this matrix.
   *
   * @param s A constant.
   * @returns This matrix.
   */
  Matrix4x4 &operator-=(double s) {
    for (auto &element : elements) {
      element -= s;
    }

    return *this;
  }

  /**
   * Multiplies this matrix with another \f$4 \times 4\f$ matrix and copies the
   * result into this instance.
   *
   * Note that this is not an element-wise multiplication, but [matrix
   * multiplication](https://en.wikipedia.org/wiki/Matrix_multiplication).
   *
   * @param m A \f$4 \times 4\f$ matrix to multiply with.
   * @returns This matrix.
   */
  Matrix4x4 &operator*=(const Matrix4x4 &m) { return this->copy(*this * m); }

  /**
   * Multiplies the elements of this matrix with the specified constant.
   *
   * @param s A constant.
   * @returns This matrix.
   */
  Matrix4x4 &operator*=(double s) {
    for (auto &element : elements) {
      element *= s;
    }

    return *this;
  }

  /**
   * Divides the elements of this matrix by the corresponding elements of
   * the specified \f$3 \times 3\f$ matrix.
   *
   * @param m A \f$4 \times 4\f$ matrix.
   * @returns This matrix.
   */
  Matrix4x4 &operator/=(const Matrix4x4 &m) {
    for (auto i = 0; i < 16; ++i) {
      elements[i] /= m.elements[i];
    }

    return *this;
  }

  /**
   * Divides the elements of this matrix with the specified constant.
   *
   * @param s A constant.
   * @returns This matrix.
   */
  Matrix4x4 &operator/=(double s) {
    for (auto &element : elements) {
      element /= s;
    }

    return *this;
  }

  /**
   * Returns whether two \f$4 \times 4\f$ matrices are equal.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param b Another \f$4 \times 4\f$ matrix.
   * @returns `true` if `a` equals `b`, `false` otherwise.
   */
  friend bool operator==(const Matrix4x4 &a, const Matrix4x4 &b) = default;

  /**
   * Adds two \f$4 \times 4\f$ matrices.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param b Another \f$4 \times 4\f$ matrix.
   * @returns The sum of `a` and `b`.
   */
  friend Matrix4x4 operator+(const Matrix4x4 &a, const Matrix4x4 &b) {
    // clang-format off
    return Matrix4x4(a.n11 + b.n11, a.n12 + b.n12, a.n13 + b.n13, a.n14 + b.n14,
                     a.n21 + b.n21, a.n22 + b.n22, a.n23 + b.n23, a.n24 + b.n24,
                     a.n31 + b.n31, a.n32 + b.n32, a.n33 + b.n33, a.n34 + b.n34,
                     a.n41 + b.n41, a.n42 + b.n42, a.n43 + b.n43, a.n44 + b.n44);
    // clang-format on
  }

  /**
   * Adds a constant to all elements of a \f$4 \times 4\f$ matrix.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when adding `s` to all elements of `a`.
   */
  friend Matrix4x4 operator+(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 + s, a.n12 + s, a.n13 + s, a.n14 + s,
                     a.n21 + s, a.n22 + s, a.n23 + s, a.n24 + s,
                     a.n31 + s, a.n32 + s, a.n33 + s, a.n34 + s,
                     a.n41 + s, a.n42 + s, a.n43 + s, a.n44 + s);
    // clang-format on
  }

  /**
   * Adds a constant to all elements of a \f$4 \times 4\f$ matrix.
   *
   * @param s A constant.
   * @param a A \f$4 \times 4\f$ matrix.
   * @returns The resulting matrix when adding `s` to all elements of `a`.
   */
  friend Matrix4x4 operator+(double s, const Matrix4x4 &a) { return a + s; }

  /**
   * Substracts 2 \f$4 \times 4\f$ matrices.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param b Another \f$4 \times 4\f$ matrix.
   * @returns The difference of `a` and `b`.
   */
  friend Matrix4x4 operator-(const Matrix4x4 &a, const Matrix4x4 &b) {
    // clang-format off
    return Matrix4x4(a.n11 - b.n11, a.n12 - b.n12, a.n13 - b.n13, a.n14 - b.n14,
                     a.n21 - b.n21, a.n22 - b.n22, a.n23 - b.n23, a.n24 - b.n24,
                     a.n31 - b.n31, a.n32 - b.n32, a.n33 - b.n33, a.n34 - b.n34,
                     a.n41 - b.n41, a.n42 - b.n42, a.n43 - b.n43, a.n44 - b.n44);
    // clang-format on
  }

  /**
   * Substracts a constant from all elements of a \f$4 \times 4\f$ matrix.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when substracting `s` from all elements of
   * `a`.
   */
  friend Matrix4x4 operator-(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 - s, a.n12 - s, a.n13 - s, a.n14 - s,
                     a.n21 - s, a.n22 - s, a.n23 - s, a.n24 - s,
                     a.n31 - s, a.n32 - s, a.n33 - s, a.n34 - s,
                     a.n41 - s, a.n42 - s, a.n43 - s, a.n44 - s);
    // clang-format on
  }

  /**
   * Substracts a \f$4 \times 4\f$ matrix from a \f$4 \times 4\f$ constant
   * matrix.
   *
   * @param s A constant for a \f$4 \times 4\f$ constant matrix.
   * @param a A \f$4 \times 4\f$ matrix.
   * @returns The resulting matrix when substracting `a` from the constant
   * matrix of `s`.
   */
  friend Matrix4x4 operator-(double s, const Matrix4x4 &a) {
    // clang-format off
    return Matrix4x4(s - a.n11, s - a.n12, s - a.n13, s - a.n14,
                     s - a.n21, s - a.n22, s - a.n23, s - a.n24,
                     s - a.n31, s - a.n32, s - a.n33, s - a.n34,
                     s - a.n41, s - a.n42, s - a.n43, s - a.n44);
    // clang-format on
  }

  /**
   * Multiplies two \f$4 \times 4\f$ matrices.
   *
   * Note that this is not an element-wise multiplication, but [matrix
   * multiplication](https://en.wikipedia.org/wiki/Matrix_multiplication).
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param b Another \f$4 \times 4\f$ matrix.
   * @returns The matrix product of `a` and `b`.
   */
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

  /**
   * Multiplies all elements of a \f$4 \times 4\f$ matrix with a constant.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when multiplying the elements of `a` with
   * `s`.
   */
  friend Matrix4x4 operator*(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 * s, a.n12 * s, a.n13 * s, a.n14 * s,
                     a.n21 * s, a.n22 * s, a.n23 * s, a.n24 * s,
                     a.n31 * s, a.n32 * s, a.n33 * s, a.n34 * s,
                     a.n41 * s, a.n42 * s, a.n43 * s, a.n44 * s);
    // clang-format on
  }

  /**
   * Multiplies all elements of a \f$4 \times 4\f$ matrix with a constant.
   *
   * @param s A constant.
   * @param a A \f$4 \times 4\f$ matrix.
   * @returns The resulting matrix when multiplying the elements of `a` with
   * `s`.
   */
  friend Matrix4x4 operator*(double s, const Matrix4x4 &a) { return a * s; }

  /**
   * Multiplies a \f$4 \times 4\f$ matrix with a four-dimensional vector.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param v A four-dimensional vector.
   * @returns The product of `a` and `v`.
   */
  friend Vector4 operator*(const Matrix4x4 &a, const Vector4 &v) {
    return Vector4(a.n11 * v.x + a.n12 * v.y + a.n13 * v.z + a.n14 * v.w,
                   a.n21 * v.x + a.n22 * v.y + a.n23 * v.z + a.n24 * v.w,
                   a.n31 * v.x + a.n32 * v.y + a.n33 * v.z + a.n34 * v.w,
                   a.n41 * v.x + a.n42 * v.y + a.n43 * v.z + a.n44 * v.w);
  }

  /**
   * Returns the element-wise division of two \f$4 \times 4\f$ matrices.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param b Another \f$4 \times 4\f$ matrix.
   * @returns The element-wise division of `a` and `b`.
   */
  friend Matrix4x4 operator/(const Matrix4x4 &a, const Matrix4x4 &b) {
    // clang-format off
    return Matrix4x4(a.n11 / b.n11, a.n12 / b.n12, a.n13 / b.n13, a.n14 / b.n14,
                     a.n21 / b.n21, a.n22 / b.n22, a.n23 / b.n23, a.n24 / b.n24,
                     a.n31 / b.n31, a.n32 / b.n32, a.n33 / b.n33, a.n34 / b.n34,
                     a.n41 / b.n41, a.n42 / b.n42, a.n43 / b.n43, a.n44 / b.n44);
    // clang-format on
  }

  /**
   * Divides all elements of a \f$4 \times 4\f$ matrix by a constant.
   *
   * @param a A \f$4 \times 4\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when dividing the elements of `a` by `s`.
   */
  friend Matrix4x4 operator/(const Matrix4x4 &a, double s) {
    // clang-format off
    return Matrix4x4(a.n11 / s, a.n12 / s, a.n13 / s, a.n14 / s,
                     a.n21 / s, a.n22 / s, a.n23 / s, a.n24 / s,
                     a.n31 / s, a.n32 / s, a.n33 / s, a.n34 / s,
                     a.n41 / s, a.n42 / s, a.n43 / s, a.n44 / s);
    // clang-format on
  }

  /**
   * Returns the element-wise division of a \f$4 \times 4\f$ constant matrix and
   * a \f$4 \times 4\f$ matrix.
   *
   * @param s A constant for a \f$4 \times 4\f$ constant matrix.
   * @param a Another \f$4 \times 4\f$ matrix.
   * @returns The element-wise division of the constant matrix and `a`.
   */
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
