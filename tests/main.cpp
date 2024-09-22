#include "gtest/gtest.h"

#include "math/Matrix3x3Tests.hpp"
#include "math/Matrix4x4Tests.hpp"
#include "math/Vector3Tests.hpp"
#include "math/Vector4Tests.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}