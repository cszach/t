#include "cameras/Camera.hpp"

#ifndef ORTHOGRAPHICCAMERA_HPP
#define ORTHOGRAPHICCAMERA_HPP

namespace t {

class OrthographicCamera : public Camera {
public:
  double left;
  double right;
  double top;
  double bottom;
  double near;
  double far;

  OrthographicCamera(double _left, double _right, double _top, double _bottom,
                     double _near, double _far)
      : Camera(Matrix4x4(
            2 / (_right - _left), 0, 0, -(_right + _left) / (_right - _left), 0,
            2 / (_top - _bottom), 0, -(_top + _bottom) / (_top - _bottom), 0, 0,
            -2 / (_far - _near), -(_far + _near) / (_far - _near), 0, 0, 0, 1)),
        left(_left), right(_right), top(_top), bottom(_bottom), near(_near),
        far(_far) {};
};

} // namespace t

#endif // ORTHOGRAPHICCAMERA_HPP