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

/**
 * The \f$3 \times 3\f$ matrix class.
 *
 * \ingroup math
 */
class Matrix3x3 {
public:
  std::array<double, 9> elements; /**< The array containing the elements of this
                                     matrix in row-major order. */

  /**
   * Returns a \f$3 \times 3\f$ identity matrix.
   *
   * @returns A \f$3 \times 3\f$ identity matrix.
   */
  static Matrix3x3 identity() { return Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); }

  /**
   * Returns a \f$3 \times 3\f$ zero matrix.
   *
   * @returns A \f$3 \times 3\f$ zero matrix.
   */
  static Matrix3x3 zero() { return Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0); }

  /**
   * Creates a new \f$3 \times 3\f$ matrix with the specified elements.
   *
   * @param _n11 The \f$(1, 1)\f$ element of the new matrix.
   * @param _n12 The \f$(1, 2)\f$ element of the new matrix.
   * @param _n13 The \f$(1, 3)\f$ element of the new matrix.
   * @param _n21 The \f$(2, 1)\f$ element of the new matrix.
   * @param _n22 The \f$(2, 2)\f$ element of the new matrix.
   * @param _n23 The \f$(2, 3)\f$ element of the new matrix.
   * @param _n31 The \f$(3, 1)\f$ element of the new matrix.
   * @param _n32 The \f$(3, 2)\f$ element of the new matrix.
   * @param _n33 The \f$(3, 3)\f$ element of the new matrix.
   */
  Matrix3x3(double _n11, double _n12, double _n13, double _n21, double _n22,
            double _n23, double _n31, double _n32, double _n33)
      : elements({_n11, _n12, _n13, _n21, _n22, _n23, _n31, _n32, _n33}) {}

  /**
   * Returns a copy of this matrix.
   *
   * @returns A copy of this matrix.
   */
  Matrix3x3 clone() const {
    return Matrix3x3(n11, n12, n13, n21, n22, n23, n31, n32, n33);
  }

  /**
   * Copies the elements of another \f$3 \times 3\f$ matrix into this matrix.
   *
   * @param source The \f$3 \times 3\f$ matrix to copy from.
   * @returns This matrix.
   */
  Matrix3x3 &copy(const Matrix3x3 &source) {
    for (auto i = 0; i < 9; ++i) {
      elements[i] = source.elements[i];
    }

    return *this;
  }

  /**
   * Sets the elements of this matrix.

   * @param _n11 The new \f$(1, 1)\f$ element of this matrix.
   * @param _n12 The new \f$(1, 2)\f$ element of this matrix.
   * @param _n13 The new \f$(1, 3)\f$ element of this matrix.
   * @param _n21 The new \f$(2, 1)\f$ element of this matrix.
   * @param _n22 The new \f$(2, 2)\f$ element of this matrix.
   * @param _n23 The new \f$(2, 3)\f$ element of this matrix.
   * @param _n31 The new \f$(3, 1)\f$ element of this matrix.
   * @param _n32 The new \f$(3, 2)\f$ element of this matrix.
   * @param _n33 The new \f$(3, 3)\f$ element of this matrix.
   * @returns This matrix.
   */
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

  /**
   * Gets the element at the specified row and column of this matrix with bounds
   * checking.
   *
   * @param row The 0-based index of the row of the element.
   * @param column The 0-based index of the column of the element.
   * @returns The element at the specified row and column of this matrix.
   * @throws std::out_of_range if the row or column is out of bounds.
   *
   * @see {@link #operator[]} for accessing without bounds checking.
   */
  double get(int row, int column) const {
    return elements.at(row * 3 + column);
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
  Matrix3x3 &set(int row, int column, int value) {
    elements.at(row * 3 + column) = value;
    return *this;
  }

  /**
   * Resets this matrix to the \f$3 \times 3\f$ identity matrix.
   *
   * @returns This matrix.
   */
  Matrix3x3 &reset() { return set(1, 0, 0, 0, 1, 0, 0, 0, 1); }

  /**
   * Returns the [determinant](https://en.wikipedia.org/wiki/Determinant) of
   * this matrix.
   *
   * @returns The determinant of this matrix.
   */
  double determinant() const {
    return n11 * n22 * n33 + n12 * n23 * n31 + n13 * n21 * n32 -
           n11 * n23 * n32 - n12 * n21 * n33 - n13 * n22 * n31;
  }

  /**
   * Returns the [transpose](https://en.wikipedia.org/wiki/Transpose) of this
   * matrix.
   *
   * Note that this method does not modify this instance.
   *
   * @returns The transpose of this matrix.
   */
  Matrix3x3 transpose() const {
    return Matrix3x3(n11, n21, n31, n12, n22, n32, n13, n23, n33);
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

  /**
   * Returns the element at the specified index of this matrix without bounds
   * checking and assuming row-major ordering.
   *
   * The element at row \f$i\f$ and column \f$j\f$ of this matrix has the index
   * \f$3i + j\f$ assuming \f$i\f$ and \f$j\f$ are zero-based.
   *
   * @param index The 0-based index of the element in row-major order.
   * @returns The element at the specified index of this matrix.
   *
   * @see {@link #get} for accessing with bounds checking.
   */
  double operator[](std::size_t index) const { return elements[index]; }

  /**
   * Adds the specified \f$3 \times 3\f$ matrix to this matrix.
   *
   * @param m A \f$3 \times 3\f$ matrix.
   * @returns This matrix.
   */
  Matrix3x3 &operator+=(const Matrix3x3 &m) {
    for (int i = 0; i < 9; ++i) {
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
  Matrix3x3 &operator+=(double s) {
    for (auto &element : elements) {
      element += s;
    }

    return *this;
  }

  /**
   * Substracts the specified \f$3 \times 3\f$ matrix from this matrix.
   *
   * @param m A \f$3 \times 3\f$ matrix.
   * @returns This matrix.
   */
  Matrix3x3 &operator-=(const Matrix3x3 &m) {
    for (int i = 0; i < 9; ++i) {
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
  Matrix3x3 &operator-=(double s) {
    for (auto &element : elements) {
      element -= s;
    }

    return *this;
  }

  /**
   * Multiplies this matrix with another \f$3 \times 3\f$ matrix and copies the
   * result into this instance.
   *
   * Note that this is not an element-wise multiplication, but [matrix
   * multiplication](https://en.wikipedia.org/wiki/Matrix_multiplication).
   *
   * @param m A \f$3 \times 3\f$ matrix to multiply with.
   * @returns This matrix.
   */
  Matrix3x3 &operator*=(const Matrix3x3 &m) { return this->copy(*this * m); }

  /**
   * Multiplies the elements of this matrix with the specified constant.
   *
   * @param s A constant.
   * @returns This matrix.
   */
  Matrix3x3 &operator*=(double s) {
    for (auto &element : elements) {
      element *= s;
    }

    return *this;
  }

  /**
   * Divides the elements of this matrix by the corresponding elements of
   * the specified \f$3 \times 3\f$ matrix.
   *
   * @param m A \f$3 \times 3\f$ matrix.
   * @returns This matrix.
   */
  Matrix3x3 &operator/=(const Matrix3x3 &m) {
    for (int i = 0; i < 9; ++i) {
      elements[i] /= m[i];
    }

    return *this;
  }

  /**
   * Divides the elements of this matrix with the specified constant.
   *
   * @param s A constant.
   * @returns This matrix.
   */
  Matrix3x3 &operator/=(double s) {
    for (auto &element : elements) {
      element /= s;
    }

    return *this;
  }

  /**
   * Returns whether two \f$3 \times 3\f$ matrices are equal.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param b Another \f$3 \times 3\f$ matrix.
   * @returns `true` if `a` equals `b`, `false` otherwise.
   */
  friend bool operator==(const Matrix3x3 &a, const Matrix3x3 &b) = default;

  /**
   * Adds two \f$3 \times 3\f$ matrices.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param b Another \f$3 \times 3\f$ matrix.
   * @returns The sum of `a` and `b`.
   */
  friend Matrix3x3 operator+(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 + b.n11, a.n12 + b.n12, a.n13 + b.n13, a.n21 + b.n21,
                     a.n22 + b.n22, a.n23 + b.n23, a.n31 + b.n31, a.n32 + b.n32,
                     a.n33 + b.n33);
  }

  /**
   * Adds a constant to all elements of a \f$3 \times 3\f$ matrix.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when adding `s` to all elements of `a`.
   */
  friend Matrix3x3 operator+(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 + s, a.n12 + s, a.n13 + s, a.n21 + s, a.n22 + s,
                     a.n23 + s, a.n31 + s, a.n32 + s, a.n33 + s);
  }

  /**
   * Adds a constant to all elements of a \f$3 \times 3\f$ matrix.
   *
   * @param s A constant.
   * @param a A \f$3 \times 3\f$ matrix.
   * @returns The resulting matrix when adding `s` to all elements of `a`.
   */
  friend Matrix3x3 operator+(double s, const Matrix3x3 &a) { return a + s; }

  /**
   * Substracts 2 \f$3 \times 3\f$ matrices.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param b Another \f$3 \times 3\f$ matrix.
   * @returns The difference of `a` and `b`.
   */
  friend Matrix3x3 operator-(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 - b.n11, a.n12 - b.n12, a.n13 - b.n13, a.n21 - b.n21,
                     a.n22 - b.n22, a.n23 - b.n23, a.n31 - b.n31, a.n32 - b.n32,
                     a.n33 - b.n33);
  }

  /**
   * Substracts a constant from all elements of a \f$3 \times 3\f$ matrix.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when substracting `s` from all elements of
   * `a`.
   */
  friend Matrix3x3 operator-(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 - s, a.n12 - s, a.n13 - s, a.n21 - s, a.n22 - s,
                     a.n23 - s, a.n31 - s, a.n32 - s, a.n33 - s);
  }

  /**
   * Substracts a \f$3 \times 3\f$ matrix from a \f$3 \times 3\f$ constant
   * matrix.
   *
   * @param s A constant for a \f$3 \times 3\f$ constant matrix.
   * @param a A \f$3 \times 3\f$ matrix.
   * @returns The resulting matrix when substracting `a` from the constant
   * matrix of `s`.
   */
  friend Matrix3x3 operator-(double s, const Matrix3x3 &a) {
    return Matrix3x3(s - a.n11, s - a.n12, s - a.n13, s - a.n21, s - a.n22,
                     s - a.n23, s - a.n31, s - a.n32, s - a.n33);
  }

  /**
   * Multiplies two \f$3 \times 3\f$ matrices.
   *
   * Note that this is not an element-wise multiplication, but [matrix
   * multiplication](https://en.wikipedia.org/wiki/Matrix_multiplication).
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param b Another \f$3 \times 3\f$ matrix.
   * @returns The matrix product of `a` and `b`.
   */
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

  /**
   * Multiplies all elements of a \f$3 \times 3\f$ matrix with a constant.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when multiplying all elements of `a` with
   * `s`.
   */
  friend Matrix3x3 operator*(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 * s, a.n12 * s, a.n13 * s, a.n21 * s, a.n22 * s,
                     a.n23 * s, a.n31 * s, a.n32 * s, a.n33 * s);
  }

  /**
   * Multiplies all elements of a \f$3 \times 3\f$ matrix with a constant.
   *
   * @param s A constant.
   * @param a A \f$3 \times 3\f$ matrix.
   * @returns The resulting matrix when multiplying all elements of `a` with
   * `s`.
   */
  friend Matrix3x3 operator*(double s, const Matrix3x3 &a) { return a * s; }

  /**
   * Multiplies a \f$3 \times 3\f$ matrix with a 3D vector.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param v A 3D vector.
   * @returns The product of `a` and `v`.
   */
  friend Vector3 operator*(const Matrix3x3 &a, const Vector3 &v) {
    return Vector3(a.n11 * v.x + a.n12 * v.y + a.n13 * v.z,
                   a.n21 * v.x + a.n22 * v.y + a.n23 * v.z,
                   a.n31 * v.x + a.n32 * v.y + a.n33 * v.z);
  }

  /**
   * Returns the element-wise division of two \f$3 \times 3\f$ matrices.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param b Another \f$3 \times 3\f$ matrix.
   * @returns The element-wise division of `a` and `b`.
   */
  friend Matrix3x3 operator/(const Matrix3x3 &a, const Matrix3x3 &b) {
    return Matrix3x3(a.n11 / b.n11, a.n12 / b.n12, a.n13 / b.n13, a.n21 / b.n21,
                     a.n22 / b.n22, a.n23 / b.n23, a.n31 / b.n31, a.n32 / b.n32,
                     a.n33 / b.n33);
  }

  /**
   * Divides all elements of a \f$3 \times 3\f$ matrix by a constant.
   *
   * @param a A \f$3 \times 3\f$ matrix.
   * @param s A constant.
   * @returns The resulting matrix when dividing all elements of `a` by `s`.
   */
  friend Matrix3x3 operator/(const Matrix3x3 &a, double s) {
    return Matrix3x3(a.n11 / s, a.n12 / s, a.n13 / s, a.n21 / s, a.n22 / s,
                     a.n23 / s, a.n31 / s, a.n32 / s, a.n33 / s);
  }

  /**
   * Returns the element-wise division of a \f$3 \times 3\f$ constant matrix and
   * a \f$3 \times 3\f$ matrix.
   *
   * @param s A constant for a \f$3 \times 3\f$ constant matrix.
   * @param a Another \f$3 \times 3\f$ matrix.
   * @returns The element-wise division of the constant matrix and `a`.
   */
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