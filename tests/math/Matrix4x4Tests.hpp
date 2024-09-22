#include "math/Matrix4x4.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(Matrix4x4Tests, Constructor) {
  const auto m =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i + 1);
  }
}

TEST(Matrix4x4Tests, Clone) {
  const auto m =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto c = m.clone();

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], i + 1);
  }
}

TEST(Matrix4x4Tests, Copy) {
  auto a = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                        31, 32);
  a.copy(b);

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], i + 17);
  }
}

TEST(Matrix4x4Tests, Set) {
  auto m = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  m.set(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i + 17);
  }
}

TEST(Matrix4x4Tests, Get) {
  const auto m =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m.get(i / 4, i % 4), i + 1);
  }
}

TEST(Matrix4x4Tests, SetElement) {
  auto m = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  for (int i = 0; i < 16; i++) {
    m.set(i / 4, i % 4, i + 17);
  }

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i + 17);
  }
}

TEST(Matrix4x4Tests, Reset) {
  auto m = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  m.reset();

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m.elements[i], i % 5 == 0 ? 1 : 0);
  }
}

TEST(Matrix4x4Tests, Determinant) {
  const auto m =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  EXPECT_DOUBLE_EQ(m.determinant(), 0);
  EXPECT_DOUBLE_EQ(t::Matrix4x4::identity().determinant(), 1);
}

TEST(Matrix4x4Tests, Transpose) {
  const auto m =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto t = m.transpose();

  for (int row = 0; row < 4; row++) {
    for (int column = 0; column < 4; column++) {
      EXPECT_DOUBLE_EQ(t.get(row, column), column * 4 + row + 1);
    }
  }
}

TEST(Matrix4x4Tests, Inverse) {
  const auto m = t::Matrix4x4(0, 0, -1, 2, 0, 1, 0, 0, 9, 0, 0, 0, 0, 0, 0, 1);
  const auto i = m.inverse();

  EXPECT_DOUBLE_EQ(i.elements[0], 0);
  EXPECT_DOUBLE_EQ(i.elements[1], 0);
  EXPECT_DOUBLE_EQ(i.elements[2], 1.0 / 9);
  EXPECT_DOUBLE_EQ(i.elements[3], 0);
  EXPECT_DOUBLE_EQ(i.elements[4], 0);
  EXPECT_DOUBLE_EQ(i.elements[5], 1);
  EXPECT_DOUBLE_EQ(i.elements[6], 0);
  EXPECT_DOUBLE_EQ(i.elements[7], 0);
  EXPECT_DOUBLE_EQ(i.elements[8], -1);
  EXPECT_DOUBLE_EQ(i.elements[9], 0);
  EXPECT_DOUBLE_EQ(i.elements[10], 0);
  EXPECT_DOUBLE_EQ(i.elements[11], 2);
  EXPECT_DOUBLE_EQ(i.elements[12], 0);
  EXPECT_DOUBLE_EQ(i.elements[13], 0);
  EXPECT_DOUBLE_EQ(i.elements[14], 0);
  EXPECT_DOUBLE_EQ(i.elements[15], 1);

  const auto degenerate =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto degenerateInverse = degenerate.inverse();

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(degenerateInverse[0], 0);
  }
}

TEST(Matrix4x4Tests, SubscriptOperator) {
  const auto m =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m[i], i + 1);
  }
}

TEST(Matrix4x4Tests, AdditionAssignment) {
  auto a = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);

  a += b;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) + (i + 17));
  }

  a += 1;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) + (i + 17) + 1);
  }
}

TEST(Matrix4x4Tests, SubtractionAssignment) {
  auto a = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);

  a -= b;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) - (i + 17));
  }

  a -= 1;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1) - (i + 17) - 1);
  }
}

TEST(Matrix4x4Tests, MultiplicationAssignment) {
  auto a = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);

  a *= b;

  EXPECT_DOUBLE_EQ(a.elements[0], 250);
  EXPECT_DOUBLE_EQ(a.elements[1], 260);
  EXPECT_DOUBLE_EQ(a.elements[2], 270);
  EXPECT_DOUBLE_EQ(a.elements[3], 280);
  EXPECT_DOUBLE_EQ(a.elements[4], 618);
  EXPECT_DOUBLE_EQ(a.elements[5], 644);
  EXPECT_DOUBLE_EQ(a.elements[6], 670);
  EXPECT_DOUBLE_EQ(a.elements[7], 696);
  EXPECT_DOUBLE_EQ(a.elements[8], 986);
  EXPECT_DOUBLE_EQ(a.elements[9], 1028);
  EXPECT_DOUBLE_EQ(a.elements[10], 1070);
  EXPECT_DOUBLE_EQ(a.elements[11], 1112);
  EXPECT_DOUBLE_EQ(a.elements[12], 1354);
  EXPECT_DOUBLE_EQ(a.elements[13], 1412);
  EXPECT_DOUBLE_EQ(a.elements[14], 1470);
  EXPECT_DOUBLE_EQ(a.elements[15], 1528);

  a *= 2;

  EXPECT_DOUBLE_EQ(a.elements[0], 250 * 2);
  EXPECT_DOUBLE_EQ(a.elements[1], 260 * 2);
  EXPECT_DOUBLE_EQ(a.elements[2], 270 * 2);
  EXPECT_DOUBLE_EQ(a.elements[3], 280 * 2);
  EXPECT_DOUBLE_EQ(a.elements[4], 618 * 2);
  EXPECT_DOUBLE_EQ(a.elements[5], 644 * 2);
  EXPECT_DOUBLE_EQ(a.elements[6], 670 * 2);
  EXPECT_DOUBLE_EQ(a.elements[7], 696 * 2);
  EXPECT_DOUBLE_EQ(a.elements[8], 986 * 2);
  EXPECT_DOUBLE_EQ(a.elements[9], 1028 * 2);
  EXPECT_DOUBLE_EQ(a.elements[10], 1070 * 2);
  EXPECT_DOUBLE_EQ(a.elements[11], 1112 * 2);
  EXPECT_DOUBLE_EQ(a.elements[12], 1354 * 2);
  EXPECT_DOUBLE_EQ(a.elements[13], 1412 * 2);
  EXPECT_DOUBLE_EQ(a.elements[14], 1470 * 2);
  EXPECT_DOUBLE_EQ(a.elements[15], 1528 * 2);
}

TEST(Matrix4x4Tests, DivisionAssignment) {
  auto a = t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);

  a /= b;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1.0) / (i + 17));
  }

  a /= 2;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(a.elements[i], (i + 1.0) / (i + 17) / 2);
  }
}

TEST(Matrix4x4Tests, Equality) {
  const auto a =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto c = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
  EXPECT_FALSE(a == c);
  EXPECT_TRUE(a != c);
}

TEST(Matrix4x4Tests, Addition) {
  const auto a =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);
  const auto c = a + b;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], (i + 1) + (i + 17));
  }

  const auto d = a + 1;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1) + 1);
  }

  const auto e = 1 + a;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], (i + 1) + 1);
  }
}

TEST(Matrix4x4Tests, Subtraction) {
  const auto a =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);
  const auto c = a - b;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], (i + 1) - (i + 17));
  }

  const auto d = a - 1;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1) - 1);
  }

  const auto e = 1 - a;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], 1 - (i + 1));
  }
}

TEST(Matrix4x4Tests, Multiplication) {
  const auto a =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);
  const auto c = a * b;

  EXPECT_DOUBLE_EQ(c.elements[0], 250);
  EXPECT_DOUBLE_EQ(c.elements[1], 260);
  EXPECT_DOUBLE_EQ(c.elements[2], 270);
  EXPECT_DOUBLE_EQ(c.elements[3], 280);
  EXPECT_DOUBLE_EQ(c.elements[4], 618);
  EXPECT_DOUBLE_EQ(c.elements[5], 644);
  EXPECT_DOUBLE_EQ(c.elements[6], 670);
  EXPECT_DOUBLE_EQ(c.elements[7], 696);
  EXPECT_DOUBLE_EQ(c.elements[8], 986);
  EXPECT_DOUBLE_EQ(c.elements[9], 1028);
  EXPECT_DOUBLE_EQ(c.elements[10], 1070);
  EXPECT_DOUBLE_EQ(c.elements[11], 1112);
  EXPECT_DOUBLE_EQ(c.elements[12], 1354);
  EXPECT_DOUBLE_EQ(c.elements[13], 1412);
  EXPECT_DOUBLE_EQ(c.elements[14], 1470);
  EXPECT_DOUBLE_EQ(c.elements[15], 1528);

  const auto d = a * 2;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1) * 2);
  }

  const auto e = 2 * a;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], (i + 1) * 2);
  }
}

TEST(Matrix4x4Tests, Division) {
  const auto a =
      t::Matrix4x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  const auto b = t::Matrix4x4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                              29, 30, 31, 32);
  const auto c = a / b;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(c.elements[i], (i + 1.0) / (i + 17));
  }

  const auto d = a / 2;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(d.elements[i], (i + 1.0) / 2);
  }

  const auto e = 2 / a;

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(e.elements[i], 2.0 / (i + 1));
  }
}

TEST(Matrix4x4Tests, Identity) {
  const auto m = t::Matrix4x4::identity();

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(m[i], i % 5 == 0 ? 1 : 0);
  }
}

TEST(Matrix4x4Tests, FromTranslation) {
  const auto actual = t::Matrix4x4::fromTranslation(t::Vector3(1, 2, 3));
  const auto expected =
      t::Matrix4x4(1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1);

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(actual.elements[i], expected.elements[i]);
  }
}

TEST(Matrix4x4Tests, FromSingleAxisRotation) {
  const auto v = t::Vector4(1, 2, 3, 1);

  // x rotation

  const auto rotationX = t::Matrix4x4::fromRotation(
      t::EulerRotation(M_PI / 2, 0, 0, t::EulerRotationOrder::Xyz));

  const auto xRotatedV = rotationX * v;

  EXPECT_DOUBLE_EQ(xRotatedV.x, 1);
  EXPECT_DOUBLE_EQ(xRotatedV.y, -3);
  EXPECT_DOUBLE_EQ(xRotatedV.z, 2);

  // y rotation

  const auto rotationY = t::Matrix4x4::fromRotation(
      t::EulerRotation(0, M_PI / 2, 0, t::EulerRotationOrder::Xyz));

  const auto yRotatedV = rotationY * v;

  EXPECT_DOUBLE_EQ(yRotatedV.x, 3);
  EXPECT_DOUBLE_EQ(yRotatedV.y, 2);
  EXPECT_DOUBLE_EQ(yRotatedV.z, -1);

  // z rotation

  const auto rotationZ = t::Matrix4x4::fromRotation(
      t::EulerRotation(0, 0, M_PI / 2, t::EulerRotationOrder::Xyz));

  const auto zRotatedV = rotationZ * v;

  EXPECT_DOUBLE_EQ(zRotatedV.x, -2);
  EXPECT_DOUBLE_EQ(zRotatedV.y, 1);
  EXPECT_DOUBLE_EQ(zRotatedV.z, 3);
}

TEST(Matrix4x4Tests, FromXYZRotation) {
  const auto v = t::Vector4(1, 2, 3, 1);

  const auto rotationXyz = t::Matrix4x4::fromRotation(t::EulerRotation(
      M_PI / 2, M_PI / 2, M_PI / 2, t::EulerRotationOrder::Xyz));

  const auto xyzRotatedV = rotationXyz * v;

  EXPECT_DOUBLE_EQ(xyzRotatedV.x, 3);
  EXPECT_DOUBLE_EQ(xyzRotatedV.y, 2);
  EXPECT_DOUBLE_EQ(xyzRotatedV.z, -1);

  const auto rotationYxz = t::Matrix4x4::fromRotation(t::EulerRotation(
      M_PI / 2, M_PI / 2, M_PI / 2, t::EulerRotationOrder::Yxz));

  const auto yxzRotatedV = rotationYxz * v;

  EXPECT_DOUBLE_EQ(yxzRotatedV.x, -1);
  EXPECT_DOUBLE_EQ(yxzRotatedV.y, 3);
  EXPECT_DOUBLE_EQ(yxzRotatedV.z, 2);

  const auto rotationZyx = t::Matrix4x4::fromRotation(t::EulerRotation(
      M_PI / 2, M_PI / 2, M_PI / 2, t::EulerRotationOrder::Zyx));

  const auto zyxRotatedV = rotationZyx * v;

  EXPECT_DOUBLE_EQ(zyxRotatedV.x, 3);
  EXPECT_DOUBLE_EQ(zyxRotatedV.y, -2);
  EXPECT_DOUBLE_EQ(zyxRotatedV.z, 1);
}

TEST(Matrix4x4Tests, FromScale) {
  const auto actual = t::Matrix4x4::fromScale(t::Vector3(1, 2, 3));
  // clang-format off
  const auto expected =
      t::Matrix4x4(1, 0, 0, 0,
                   0, 2, 0, 0,
                   0, 0, 3, 0,
                   0, 0, 0, 1);
  // clang-format on

  for (int i = 0; i < 16; i++) {
    EXPECT_DOUBLE_EQ(actual.elements[i], expected.elements[i]);
  }
}