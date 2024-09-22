#include "math/Matrix3x3.hpp"
#include <gtest/gtest.h>

TEST(Matrix3x3Tests, Constructor) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i + 1);
  }
}

TEST(Matrix3x3Tests, Clone) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto c = m.clone();

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], i + 1);
  }
}

TEST(Matrix3x3Tests, Copy) {
  auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);
  a.copy(b);

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], i + 10);
  }
}

TEST(Matrix3x3Tests, Set) {
  auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  m.set(10, 11, 12, 13, 14, 15, 16, 17, 18);

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i + 10);
  }
}

TEST(Matrix3x3Tests, Get) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m.get(i / 3, i % 3), i + 1);
  }
}

TEST(Matrix3x3Tests, SetElement) {
  auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

  for (int i = 0; i < 9; i++) {
    m.set(i / 3, i % 3, i + 10);
  }

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i + 10);
  }
}

TEST(Matrix3x3Tests, Reset) {
  auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  m.reset();

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i % 4 == 0 ? 1 : 0);
  }
}

TEST(Matrix3x3Tests, Determinant) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

  EXPECT_DOUBLE_EQ(m.determinant(), 0);
  EXPECT_DOUBLE_EQ(t::Matrix3x3::identity().determinant(), 1);
}

TEST(Matrix3x3Tests, Transpose) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto t = m.transpose();

  for (int row = 0; row < 3; row++) {
    for (int column = 0; column < 3; column++) {
      EXPECT_DOUBLE_EQ(t.get(row, column), column * 3 + row + 1);
    }
  }
}

TEST(Matrix3x3Tests, Inverse) {
  const auto m = t::Matrix3x3(1, 2, 3, 0, 1, 4, 5, 6, 0);
  const auto i = m.inverse();

  EXPECT_DOUBLE_EQ(i.elements[0], -24);
  EXPECT_DOUBLE_EQ(i.elements[1], 18);
  EXPECT_DOUBLE_EQ(i.elements[2], 5);
  EXPECT_DOUBLE_EQ(i.elements[3], 20);
  EXPECT_DOUBLE_EQ(i.elements[4], -15);
  EXPECT_DOUBLE_EQ(i.elements[5], -4);
  EXPECT_DOUBLE_EQ(i.elements[6], -5);
  EXPECT_DOUBLE_EQ(i.elements[7], 4);
  EXPECT_DOUBLE_EQ(i.elements[8], 1);

  const auto degenerate = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto degenerateInverse = degenerate.inverse();

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(degenerateInverse.elements[i], 0);
  }
}

TEST(Matrix3x3Tests, SubscriptOperator) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m[i], i + 1);
  }
}

TEST(Matrix3x3Tests, AdditionAssignment) {
  auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);

  a += b;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) + (i + 10));
  }

  a += 1;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) + (i + 10) + 1);
  }
}

TEST(Matrix3x3Tests, SubtractionAssignment) {
  auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);

  a -= b;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) - (i + 10));
  }

  a -= 1;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) - (i + 10) - 1);
  }
}

TEST(Matrix3x3Tests, MultiplicationAssignment) {
  auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);

  a *= b;

  EXPECT_DOUBLE_EQ(a.elements[0], 84);
  EXPECT_DOUBLE_EQ(a.elements[1], 90);
  EXPECT_DOUBLE_EQ(a.elements[2], 96);
  EXPECT_DOUBLE_EQ(a.elements[3], 201);
  EXPECT_DOUBLE_EQ(a.elements[4], 216);
  EXPECT_DOUBLE_EQ(a.elements[5], 231);
  EXPECT_DOUBLE_EQ(a.elements[6], 318);
  EXPECT_DOUBLE_EQ(a.elements[7], 342);
  EXPECT_DOUBLE_EQ(a.elements[8], 366);

  a *= 2;

  EXPECT_DOUBLE_EQ(a.elements[0], 84 * 2);
  EXPECT_DOUBLE_EQ(a.elements[1], 90 * 2);
  EXPECT_DOUBLE_EQ(a.elements[2], 96 * 2);
  EXPECT_DOUBLE_EQ(a.elements[3], 201 * 2);
  EXPECT_DOUBLE_EQ(a.elements[4], 216 * 2);
  EXPECT_DOUBLE_EQ(a.elements[5], 231 * 2);
  EXPECT_DOUBLE_EQ(a.elements[6], 318 * 2);
  EXPECT_DOUBLE_EQ(a.elements[7], 342 * 2);
  EXPECT_DOUBLE_EQ(a.elements[8], 366 * 2);
}

TEST(Matrix3x3Tests, DivisionAssignment) {
  auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);

  a /= b;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1.0) / (i + 10));
  }

  a /= 2;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1.0) / (i + 10) / 2);
  }
}

TEST(Matrix3x3Tests, Equality) {
  const auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto c = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);
}

TEST(Matrix3x3Tests, Identity) {
  const auto m = t::Matrix3x3::identity();

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(m[i], i % 4 == 0 ? 1 : 0);
  }
}

TEST(Matrix3x3Tests, Addition) {
  const auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);
  const auto c = a + b;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], (i + 1) + (i + 10));
  }

  const auto d = a + 1;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1) + 1);
  }

  const auto e = 1 + a;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], (i + 1) + 1);
  }
}

TEST(Matrix3x3Tests, Subtraction) {
  const auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);
  const auto c = a - b;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], (i + 1) - (i + 10));
  }

  const auto d = a - 1;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1) - 1);
  }

  const auto e = 1 - a;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], 1 - (i + 1));
  }
}

TEST(Matrix3x3Tests, Multiplication) {
  const auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);
  const auto c = a * b;

  EXPECT_DOUBLE_EQ(c.elements[0], 84);
  EXPECT_DOUBLE_EQ(c.elements[1], 90);
  EXPECT_DOUBLE_EQ(c.elements[2], 96);
  EXPECT_DOUBLE_EQ(c.elements[3], 201);
  EXPECT_DOUBLE_EQ(c.elements[4], 216);
  EXPECT_DOUBLE_EQ(c.elements[5], 231);
  EXPECT_DOUBLE_EQ(c.elements[6], 318);
  EXPECT_DOUBLE_EQ(c.elements[7], 342);
  EXPECT_DOUBLE_EQ(c.elements[8], 366);

  const auto d = a * 2;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1) * 2);
  }

  const auto e = 2 * a;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], (i + 1) * 2);
  }
}

TEST(Matrix3x3Tests, MatrixVectorMultiplication) {
  const auto m = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto v = t::Vector3(1, 2, 3);
  const auto r = m * v;

  EXPECT_DOUBLE_EQ(r.x, 14);
  EXPECT_DOUBLE_EQ(r.y, 32);
  EXPECT_DOUBLE_EQ(r.z, 50);
}

TEST(Matrix3x3Tests, Division) {
  const auto a = t::Matrix3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const auto b = t::Matrix3x3(10, 11, 12, 13, 14, 15, 16, 17, 18);
  const auto c = a / b;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], (i + 1.0) / (i + 10));
  }

  const auto d = a / 2;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1.0) / 2);
  }

  const auto e = 2 / a;

  for (int i = 0; i < 9; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], 2 / (i + 1.0));
  }
}
