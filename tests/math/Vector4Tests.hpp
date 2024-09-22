#include "math/Vector4.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(Vector4Tests, Constructor) {
  const auto v = t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v.x, 1);
  EXPECT_DOUBLE_EQ(v.y, 2);
  EXPECT_DOUBLE_EQ(v.z, 3);
  EXPECT_DOUBLE_EQ(v.w, 4);

  const auto v2 = t::Vector4(t::Vector3(1, 2, 3), 4);

  EXPECT_DOUBLE_EQ(v2.x, 1);
  EXPECT_DOUBLE_EQ(v2.y, 2);
  EXPECT_DOUBLE_EQ(v2.z, 3);
  EXPECT_DOUBLE_EQ(v2.w, 4);
}

TEST(Vector4Tests, Clone) {
  const auto v = t::Vector4(1, 2, 3, 4);
  const auto c = v.clone();

  EXPECT_DOUBLE_EQ(c.x, 1);
  EXPECT_DOUBLE_EQ(c.y, 2);
  EXPECT_DOUBLE_EQ(c.z, 3);
  EXPECT_DOUBLE_EQ(c.w, 4);
}

TEST(Vector4Tests, Copy) {
  auto v = t::Vector4(1, 2, 3, 4);
  v.copy(t::Vector4(5, 6, 7, 8));

  EXPECT_DOUBLE_EQ(v.x, 5);
  EXPECT_DOUBLE_EQ(v.y, 6);
  EXPECT_DOUBLE_EQ(v.z, 7);
  EXPECT_DOUBLE_EQ(v.w, 8);
}

TEST(Vector4Tests, Set) {
  auto v = t::Vector4(1, 2, 3, 4);
  v.set(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 5);
  EXPECT_DOUBLE_EQ(v.y, 6);
  EXPECT_DOUBLE_EQ(v.z, 7);
  EXPECT_DOUBLE_EQ(v.w, 8);
}

TEST(Vector4Tests, ToVector3) {
  const auto v = t::Vector4(1, 2, 3, 4).toVector3();

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 4);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 4);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 4);
}

TEST(Vector4Tests, Length) {
  const auto v = t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v.length(), std::sqrt(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4));
}

TEST(Vector4Tests, Unit) {
  const auto v = t::Vector4(1, 2, 3, 4).unit();
  const auto length = std::sqrt(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4);

  EXPECT_DOUBLE_EQ(v.x, 1 / length);
  EXPECT_DOUBLE_EQ(v.y, 2 / length);
  EXPECT_DOUBLE_EQ(v.z, 3 / length);
  EXPECT_DOUBLE_EQ(v.w, 4 / length);
}

TEST(Vector4Tests, Normalize) {
  auto v = t::Vector4(1, 2, 3, 4).normalize();
  const auto length = std::sqrt(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4);

  EXPECT_DOUBLE_EQ(v.x, 1 / length);
  EXPECT_DOUBLE_EQ(v.y, 2 / length);
  EXPECT_DOUBLE_EQ(v.z, 3 / length);
  EXPECT_DOUBLE_EQ(v.w, 4 / length);
}

TEST(Vector4Tests, Absolute) {
  auto v = t::Vector4(1, -2, 3, -4).absolute();

  EXPECT_DOUBLE_EQ(v.x, 1);
  EXPECT_DOUBLE_EQ(v.y, 2);
  EXPECT_DOUBLE_EQ(v.z, 3);
  EXPECT_DOUBLE_EQ(v.w, 4);
}

TEST(Vector4Tests, Abs) {
  auto v = t::Vector4(1, -2, 3, -4);
  v.abs();

  EXPECT_DOUBLE_EQ(v.x, 1);
  EXPECT_DOUBLE_EQ(v.y, 2);
  EXPECT_DOUBLE_EQ(v.z, 3);
  EXPECT_DOUBLE_EQ(v.w, 4);
}

TEST(Vector4Tests, Clamp) {
  auto v = t::Vector4(1, 2, 3, 4);
  v.clamp(t::Vector4(2, 3, 4, 5), t::Vector4(4, 5, 6, 7));

  EXPECT_DOUBLE_EQ(v.x, 2);
  EXPECT_DOUBLE_EQ(v.y, 3);
  EXPECT_DOUBLE_EQ(v.z, 4);
  EXPECT_DOUBLE_EQ(v.w, 5);

  v.clamp(3, 5);

  EXPECT_DOUBLE_EQ(v.x, 3);
  EXPECT_DOUBLE_EQ(v.y, 3);
  EXPECT_DOUBLE_EQ(v.z, 4);
  EXPECT_DOUBLE_EQ(v.w, 5);
}

TEST(Vector4Tests, SubscriptOperator) {
  const auto v = t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v[0], 1);
  EXPECT_DOUBLE_EQ(v[1], 2);
  EXPECT_DOUBLE_EQ(v[2], 3);
  EXPECT_DOUBLE_EQ(v[3], 4);
  EXPECT_THROW(v[4], std::invalid_argument);
}

TEST(Vector4Tests, AdditionAssignment) {
  auto v = t::Vector4(1, 2, 3, 4);
  v += t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 6);
  EXPECT_DOUBLE_EQ(v.y, 8);
  EXPECT_DOUBLE_EQ(v.z, 10);
  EXPECT_DOUBLE_EQ(v.w, 12);

  v += 2;

  EXPECT_DOUBLE_EQ(v.x, 8);
  EXPECT_DOUBLE_EQ(v.y, 10);
  EXPECT_DOUBLE_EQ(v.z, 12);
  EXPECT_DOUBLE_EQ(v.w, 14);
}

TEST(Vector4Tests, SubtractionAssignment) {
  auto v = t::Vector4(1, 2, 3, 4);
  v -= t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, -4);
  EXPECT_DOUBLE_EQ(v.y, -4);
  EXPECT_DOUBLE_EQ(v.z, -4);
  EXPECT_DOUBLE_EQ(v.w, -4);

  v -= 2;

  EXPECT_DOUBLE_EQ(v.x, -6);
  EXPECT_DOUBLE_EQ(v.y, -6);
  EXPECT_DOUBLE_EQ(v.z, -6);
  EXPECT_DOUBLE_EQ(v.w, -6);
}

TEST(Vector4Tests, MultiplicationAssignment) {
  auto v = t::Vector4(1, 2, 3, 4);
  v *= t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 5);
  EXPECT_DOUBLE_EQ(v.y, 12);
  EXPECT_DOUBLE_EQ(v.z, 21);
  EXPECT_DOUBLE_EQ(v.w, 32);

  v *= 2;

  EXPECT_DOUBLE_EQ(v.x, 10);
  EXPECT_DOUBLE_EQ(v.y, 24);
  EXPECT_DOUBLE_EQ(v.z, 42);
  EXPECT_DOUBLE_EQ(v.w, 64);
}

TEST(Vector4Tests, DivisionAssignment) {
  auto v = t::Vector4(1, 2, 3, 4);
  v /= t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 5);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 6);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 7);
  EXPECT_DOUBLE_EQ(v.w, 4.0 / 8);

  v /= 2;

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 10);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 12);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 14);
  EXPECT_DOUBLE_EQ(v.w, 4.0 / 16);
}

TEST(Vector4Tests, Equality) {
  const auto a = t::Vector4(1, 2, 3, 4);
  const auto b = t::Vector4(1, 2, 3, 4);
  const auto c = t::Vector4(5, 6, 7, 8);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);
}

TEST(Vector4Tests, Addition) {
  const auto v = t::Vector4(1, 2, 3, 4) + t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 6);
  EXPECT_DOUBLE_EQ(v.y, 8);
  EXPECT_DOUBLE_EQ(v.z, 10);
  EXPECT_DOUBLE_EQ(v.w, 12);

  const auto v2 = t::Vector4(1, 2, 3, 4) + 5;

  EXPECT_DOUBLE_EQ(v2.x, 6);
  EXPECT_DOUBLE_EQ(v2.y, 7);
  EXPECT_DOUBLE_EQ(v2.z, 8);
  EXPECT_DOUBLE_EQ(v2.w, 9);

  const auto v3 = 5 + t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v3.x, 6);
  EXPECT_DOUBLE_EQ(v3.y, 7);
  EXPECT_DOUBLE_EQ(v3.z, 8);
  EXPECT_DOUBLE_EQ(v3.w, 9);
}

TEST(Vector4Tests, Subtraction) {
  const auto v = t::Vector4(1, 2, 3, 4) - t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, -4);
  EXPECT_DOUBLE_EQ(v.y, -4);
  EXPECT_DOUBLE_EQ(v.z, -4);
  EXPECT_DOUBLE_EQ(v.w, -4);

  const auto v2 = t::Vector4(1, 2, 3, 4) - 5;

  EXPECT_DOUBLE_EQ(v2.x, -4);
  EXPECT_DOUBLE_EQ(v2.y, -3);
  EXPECT_DOUBLE_EQ(v2.z, -2);
  EXPECT_DOUBLE_EQ(v2.w, -1);

  const auto v3 = 5 - t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v3.x, 4);
  EXPECT_DOUBLE_EQ(v3.y, 3);
  EXPECT_DOUBLE_EQ(v3.z, 2);
  EXPECT_DOUBLE_EQ(v3.w, 1);
}

TEST(Vector4Tests, Multiplication) {
  const auto v = t::Vector4(1, 2, 3, 4) * t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 5);
  EXPECT_DOUBLE_EQ(v.y, 12);
  EXPECT_DOUBLE_EQ(v.z, 21);
  EXPECT_DOUBLE_EQ(v.w, 32);

  const auto v2 = t::Vector4(1, 2, 3, 4) * 5;

  EXPECT_DOUBLE_EQ(v2.x, 5);
  EXPECT_DOUBLE_EQ(v2.y, 10);
  EXPECT_DOUBLE_EQ(v2.z, 15);
  EXPECT_DOUBLE_EQ(v2.w, 20);

  const auto v3 = 5 * t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v3.x, 5);
  EXPECT_DOUBLE_EQ(v3.y, 10);
  EXPECT_DOUBLE_EQ(v3.z, 15);
  EXPECT_DOUBLE_EQ(v3.w, 20);
}

TEST(Vector4Tests, Division) {
  const auto v = t::Vector4(1, 2, 3, 4) / t::Vector4(5, 6, 7, 8);

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 5);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 6);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 7);
  EXPECT_DOUBLE_EQ(v.w, 4.0 / 8);

  const auto v2 = t::Vector4(1, 2, 3, 4) / 5;

  EXPECT_DOUBLE_EQ(v2.x, 1.0 / 5);
  EXPECT_DOUBLE_EQ(v2.y, 2.0 / 5);
  EXPECT_DOUBLE_EQ(v2.z, 3.0 / 5);
  EXPECT_DOUBLE_EQ(v2.w, 4.0 / 5);

  const auto v3 = 5 / t::Vector4(1, 2, 3, 4);

  EXPECT_DOUBLE_EQ(v3.x, 5);
  EXPECT_DOUBLE_EQ(v3.y, 2.5);
  EXPECT_DOUBLE_EQ(v3.z, 5.0 / 3);
  EXPECT_DOUBLE_EQ(v3.w, 5.0 / 4);
}
