#include "math/Vector3.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(Vector3Tests, Constructor) {
  const auto v = t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v.x, 1);
  EXPECT_DOUBLE_EQ(v.y, 2);
  EXPECT_DOUBLE_EQ(v.z, 3);
}

TEST(Vector3Tests, Clone) {
  const auto v = t::Vector3(1, 2, 3);
  const auto c = v.clone();

  EXPECT_DOUBLE_EQ(c.x, 1);
  EXPECT_DOUBLE_EQ(c.y, 2);
  EXPECT_DOUBLE_EQ(c.z, 3);
}

TEST(Vector3Tests, Copy) {
  auto v = t::Vector3(1, 2, 3);
  v.copy(t::Vector3(4, 5, 6));

  EXPECT_DOUBLE_EQ(v.x, 4);
  EXPECT_DOUBLE_EQ(v.y, 5);
  EXPECT_DOUBLE_EQ(v.z, 6);
}

TEST(Vector3Tests, Set) {
  auto v = t::Vector3(1, 2, 3);
  v.set(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 4);
  EXPECT_DOUBLE_EQ(v.y, 5);
  EXPECT_DOUBLE_EQ(v.z, 6);
}

TEST(Vector3Tests, Length) {
  const auto v = t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v.length(), std::sqrt(1 * 1 + 2 * 2 + 3 * 3));
}

TEST(Vector3Tests, Unit) {
  const auto v = t::Vector3(1, 2, 3).unit();
  const auto length = std::sqrt(1 * 1 + 2 * 2 + 3 * 3);

  EXPECT_DOUBLE_EQ(v.x, 1 / length);
  EXPECT_DOUBLE_EQ(v.y, 2 / length);
  EXPECT_DOUBLE_EQ(v.z, 3 / length);
}

TEST(Vector3Tests, Normalize) {
  auto v = t::Vector3(1, 2, 3).normalize();
  const auto length = std::sqrt(1 * 1 + 2 * 2 + 3 * 3);

  EXPECT_DOUBLE_EQ(v.x, 1 / length);
  EXPECT_DOUBLE_EQ(v.y, 2 / length);
  EXPECT_DOUBLE_EQ(v.z, 3 / length);
}

TEST(Vector3Tests, Absolute) {
  auto v = t::Vector3(-1, 2, -3).absolute();

  EXPECT_DOUBLE_EQ(v.x, 1);
  EXPECT_DOUBLE_EQ(v.y, 2);
  EXPECT_DOUBLE_EQ(v.z, 3);
}

TEST(Vector3Tests, Abs) {
  auto v = t::Vector3(-1, 2, -3);
  v.abs();

  EXPECT_DOUBLE_EQ(v.x, 1);
  EXPECT_DOUBLE_EQ(v.y, 2);
  EXPECT_DOUBLE_EQ(v.z, 3);
}

TEST(Vector3Tests, Clamp) {
  auto v = t::Vector3(1, 2, 3);
  v.clamp(t::Vector3(2, 3, 4), t::Vector3(4, 5, 6));

  EXPECT_DOUBLE_EQ(v.x, 2);
  EXPECT_DOUBLE_EQ(v.y, 3);
  EXPECT_DOUBLE_EQ(v.z, 4);

  v.clamp(3, 5);

  EXPECT_DOUBLE_EQ(v.x, 3);
  EXPECT_DOUBLE_EQ(v.y, 3);
  EXPECT_DOUBLE_EQ(v.z, 4);
}

TEST(Vector3Tests, SubscriptOperator) {
  const auto v = t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v[0], 1);
  EXPECT_DOUBLE_EQ(v[1], 2);
  EXPECT_DOUBLE_EQ(v[2], 3);
  EXPECT_THROW(v[3], std::invalid_argument);
}

TEST(Vector3Tests, AdditionAssignment) {
  auto v = t::Vector3(1, 2, 3);
  v += t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 5);
  EXPECT_DOUBLE_EQ(v.y, 7);
  EXPECT_DOUBLE_EQ(v.z, 9);

  v += 2;

  EXPECT_DOUBLE_EQ(v.x, 7);
  EXPECT_DOUBLE_EQ(v.y, 9);
  EXPECT_DOUBLE_EQ(v.z, 11);
}

TEST(Vector3Tests, SubtractionAssignment) {
  auto v = t::Vector3(1, 2, 3);
  v -= t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, -3);
  EXPECT_DOUBLE_EQ(v.y, -3);
  EXPECT_DOUBLE_EQ(v.z, -3);

  v -= 2;

  EXPECT_DOUBLE_EQ(v.x, -5);
  EXPECT_DOUBLE_EQ(v.y, -5);
  EXPECT_DOUBLE_EQ(v.z, -5);
}

TEST(Vector3Tests, MultiplicationAssignment) {
  auto v = t::Vector3(1, 2, 3);
  v *= t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 4);
  EXPECT_DOUBLE_EQ(v.y, 10);
  EXPECT_DOUBLE_EQ(v.z, 18);

  v *= 2;

  EXPECT_DOUBLE_EQ(v.x, 8);
  EXPECT_DOUBLE_EQ(v.y, 20);
  EXPECT_DOUBLE_EQ(v.z, 36);
}

TEST(Vector3Tests, DivisionAssignment) {
  auto v = t::Vector3(1, 2, 3);
  v /= t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 4);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 5);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 6);

  v /= 2;

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 8);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 10);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 12);
}

TEST(Vector3Tests, Equality) {
  const auto a = t::Vector3(1, 2, 3);
  const auto b = t::Vector3(1, 2, 3);
  const auto c = t::Vector3(4, 5, 6);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);
}

TEST(Vector3Tests, Addition) {
  const auto v = t::Vector3(1, 2, 3) + t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 5);
  EXPECT_DOUBLE_EQ(v.y, 7);
  EXPECT_DOUBLE_EQ(v.z, 9);

  const auto v2 = t::Vector3(1, 2, 3) + 4;

  EXPECT_DOUBLE_EQ(v2.x, 5);
  EXPECT_DOUBLE_EQ(v2.y, 6);
  EXPECT_DOUBLE_EQ(v2.z, 7);

  const auto v3 = 4 + t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v3.x, 5);
  EXPECT_DOUBLE_EQ(v3.y, 6);
  EXPECT_DOUBLE_EQ(v3.z, 7);
}

TEST(Vector3Tests, Subtraction) {
  const auto v = t::Vector3(1, 2, 3) - t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, -3);
  EXPECT_DOUBLE_EQ(v.y, -3);
  EXPECT_DOUBLE_EQ(v.z, -3);

  const auto v2 = t::Vector3(1, 2, 3) - 4;

  EXPECT_DOUBLE_EQ(v2.x, -3);
  EXPECT_DOUBLE_EQ(v2.y, -2);
  EXPECT_DOUBLE_EQ(v2.z, -1);

  const auto v3 = 4 - t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v3.x, 3);
  EXPECT_DOUBLE_EQ(v3.y, 2);
  EXPECT_DOUBLE_EQ(v3.z, 1);
}

TEST(Vector3Tests, Multiplication) {
  const auto v = t::Vector3(1, 2, 3) * t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 4);
  EXPECT_DOUBLE_EQ(v.y, 10);
  EXPECT_DOUBLE_EQ(v.z, 18);

  const auto v2 = t::Vector3(1, 2, 3) * 4;

  EXPECT_DOUBLE_EQ(v2.x, 4);
  EXPECT_DOUBLE_EQ(v2.y, 8);
  EXPECT_DOUBLE_EQ(v2.z, 12);

  const auto v3 = 4 * t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v3.x, 4);
  EXPECT_DOUBLE_EQ(v3.y, 8);
  EXPECT_DOUBLE_EQ(v3.z, 12);
}

TEST(Vector3Tests, Division) {
  const auto v = t::Vector3(1, 2, 3) / t::Vector3(4, 5, 6);

  EXPECT_DOUBLE_EQ(v.x, 1.0 / 4);
  EXPECT_DOUBLE_EQ(v.y, 2.0 / 5);
  EXPECT_DOUBLE_EQ(v.z, 3.0 / 6);

  const auto v2 = t::Vector3(1, 2, 3) / 4;

  EXPECT_DOUBLE_EQ(v2.x, 1.0 / 4);
  EXPECT_DOUBLE_EQ(v2.y, 2.0 / 4);
  EXPECT_DOUBLE_EQ(v2.z, 3.0 / 4);

  const auto v3 = 4 / t::Vector3(1, 2, 3);

  EXPECT_DOUBLE_EQ(v3.x, 4);
  EXPECT_DOUBLE_EQ(v3.y, 2);
  EXPECT_DOUBLE_EQ(v3.z, 4.0 / 3);
}

TEST(Vector3Tests, FromBufferAttribute) {
  const auto bufferAttribute =
      t::BufferAttribute<double>({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3);
  const auto v = t::Vector3::fromBufferAttribute(bufferAttribute, 1);

  EXPECT_DOUBLE_EQ(v.x, 4);
  EXPECT_DOUBLE_EQ(v.y, 5);
  EXPECT_DOUBLE_EQ(v.z, 6);
}

TEST(Vector3Tests, Cross) {
  const auto a = t::Vector3(1, 0, 0);
  const auto b = t::Vector3(0, 1, 0);
  const auto c = t::Vector3::cross(a, b);

  EXPECT_DOUBLE_EQ(c.x, 0);
  EXPECT_DOUBLE_EQ(c.y, 0);
  EXPECT_DOUBLE_EQ(c.z, 1);
}

TEST(Vector3Tests, Dot) {
  const auto a = t::Vector3(1, 2, 3);
  const auto b = t::Vector3(4, 5, 6);
  const auto d = t::Vector3::dot(a, b);

  EXPECT_DOUBLE_EQ(d, 1 * 4 + 2 * 5 + 3 * 6);
}

TEST(Vector3Tests, Reflect) {
  const auto incident = t::Vector3(1, -2, 3);
  const auto surfaceOrientation = t::Vector3(0, 1, 0);
  const auto r = t::Vector3::reflect(incident, surfaceOrientation);

  EXPECT_DOUBLE_EQ(r.x, 1);
  EXPECT_DOUBLE_EQ(r.y, 2);
  EXPECT_DOUBLE_EQ(r.z, 3);
}