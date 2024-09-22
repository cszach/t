#include "math/Vector3.hpp"

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace t {

enum class EulerRotationOrder { Xyz, Xzy, Yxz, Yzx, Zxy, Zyx };
enum class TextureFormat { RgbDouble = 3, Depth = 1 };
enum class FrontFace { Clockwise = 1, CounterClockwise = -1 };
enum class CullMode { None = 0, Front = 1, Back = -1 };
#define DEFAULT_UP Vector3(0, 1, 0)

} // namespace t

#endif // CONSTANTS_HPP