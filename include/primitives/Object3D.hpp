#include "math/EulerRotation.hpp"
#include "math/Matrix4x4.hpp"
#include "math/Vector3.hpp"
#include <functional>
#include <optional>
#include <vector>

#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

namespace t {

class Object3D {
public:
  virtual ~Object3D() = default;

  std::optional<std::reference_wrapper<Object3D>> parent;
  Vector3 up = DEFAULT_UP;
  Vector3 localPosition = Vector3(0, 0, 0);
  EulerRotation localRotation = EulerRotation(0, 0, 0, EulerRotationOrder::Xyz);
  Vector3 localScale = Vector3(1, 1, 1);
  Matrix4x4 localMatrix = Matrix4x4::identity();
  Matrix4x4 modelMatrix = Matrix4x4::identity();
  std::vector<std::reference_wrapper<Object3D>> children;

  virtual bool isMesh() const { return false; }

  virtual bool isLight() const { return false; }

  Object3D &add(Object3D &child) {
    children.push_back(child);
    child.parent = *this;

    return *this;
  }
  // Object3D &lookAt(const Vector3 &target);
  // Object3D &lookAt(const Object3D &target);

  Object3D &translate(double x, double y, double z) {
    this->localPosition += Vector3(x, y, z);
    return *this;
  }

  Object3D &rotate(double x, double y, double z, EulerRotationOrder order) {
    this->localRotation.copy(this->localRotation +
                             EulerRotation(x, y, z, order));
    return *this;
  }

  Object3D &scale(double x, double y, double z) {
    this->localScale *= Vector3(x, y, z);
    return *this;
  }

  // Vector3 getWorldPosition() const;
  // EulerRotation getWorldRotation() const;
  // Vector3 getWorldScale();

  Object3D &updateLocalMatrix() {
    Matrix4x4 translationMatrix = Matrix4x4::fromTranslation(localPosition);
    Matrix4x4 rotationMatrix = Matrix4x4::fromRotation(localRotation);
    Matrix4x4 scaleMatrix = Matrix4x4::fromScale(localScale);

    localMatrix.copy(translationMatrix * rotationMatrix * scaleMatrix);
    return *this;
  }

  Object3D &updateModelMatrix() {
    if (parent) {
      modelMatrix.copy(parent.value().get().modelMatrix * this->localMatrix);
    } else {
      modelMatrix.copy(localMatrix);
    }

    return *this;
  }
};

} // namespace t

#endif // OBJECT3D_HPP