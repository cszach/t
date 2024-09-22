#include "cameras/Camera.hpp"
#include <cmath>

#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

namespace t {

class PerspectiveCamera : public Camera {
public:
  double verticalFov;
  double aspectRatio;
  double near;
  double far;

  PerspectiveCamera(double _verticalFov, double _aspectRatio, double _near,
                    double _far)
      : Camera(Matrix4x4(1.0 / (_aspectRatio * std::tan(_verticalFov / 2.0)), 0,
                         0, 0, 0, 1.0 / std::tan(_verticalFov / 2), 0, 0, 0, 0,
                         -(_far + _near) / (_far - _near),
                         (-2.0 * _far * _near) / (_far - _near), 0, 0, -1, 0)),
        verticalFov(_verticalFov), aspectRatio(_aspectRatio), near(_near),
        far(_far) {}
};

} // namespace t

#endif // PERSPECTIVECAMERA_HPP