#include "math/EulerRotation.hpp"
#include "math/Matrix4x4.hpp"
#include "math/Vector3.hpp"
#include <functional>
#include <optional>
#include <vector>

#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

namespace t {

/**
 * The 3D object class.
 *
 * A 3D object has a position, rotation, and scale in 3D space. It can also have
 * a parent and children. The most common types of 3D objects are {@linkplain
 * Mesh meshes} and groups of meshes. {@linkplain Scene Scenes}, {@linkplain
 * Camera cameras}, and {@linkplain Light lights} are special types of 3D
 * objects.
 *
 * \ingroup primitives
 */
class Object3D {
public:
  virtual ~Object3D() = default;

  std::optional<std::reference_wrapper<Object3D>> parent; /**< The parent of
                                                             this 3D object. */
  Vector3 up = DEFAULT_UP; /**< The vector pointing to the up direction in
                              object space. */
  Vector3 localPosition = Vector3(
      0, 0, 0); /**< The position of this 3D object relative to its parent. */
  EulerRotation localRotation = EulerRotation(
      0, 0, 0, EulerRotationOrder::Xyz); /**< The rotation of this 3D object
                                            relative to its parent. */
  Vector3 localScale = Vector3(
      1, 1, 1); /**< The scale of this 3D object relative to its parent. */
  Matrix4x4 localMatrix =
      Matrix4x4::identity(); /**< The matrix of the local transformation of this
                                3D object. This is calculated automatically by
                                default during the render process from {@link
                                #localPosition}, {@link #localRotation}, and
                                {@link localScale}.
                              */
  Matrix4x4 modelMatrix =
      Matrix4x4::identity(); /**< The model matrix of this 3D object,
                                transformating local space to world space. This
                                is calculated automatically by default during
                                the render process. */
  std::vector<std::reference_wrapper<Object3D>>
      children; /**< The children of this 3D object. */

  /**
   * Returns whether this 3D object is a mesh.
   *
   * Used internally before casting an {@link Object3D} to a {@link Mesh}.
   *
   * @returns `false`
   */
  virtual bool isMesh() const { return false; }

  /**
   * Returns whether this 3D object is a light.
   *
   * Used internally before casting an {@link Object3D} to a {@link Light}.
   *
   * @returns `false`
   */
  virtual bool isLight() const { return false; }

  /**
   * Adds another 3D object as a child of this 3D object.
   *
   * @returns This 3D object.
   */
  Object3D &add(Object3D &child) {
    children.push_back(child);
    child.parent = *this;

    return *this;
  }

  // Object3D &lookAt(const Vector3 &target);
  // Object3D &lookAt(const Object3D &target);

  /**
   * Translates this 3D object by the specified amounts along the x, y, and z
   * axes in local space.
   *
   * @param x The amount to translate along the x axis.
   * @param y The amount to translate along the y axis.
   * @param z The amount to translate along the z axis.
   * @returns This 3D object.
   *
   */
  Object3D &translate(double x, double y, double z) {
    this->localPosition += Vector3(x, y, z);
    return *this;
  }

  /**
   * Rotates this 3D object by the specified angles around the x, y, and z axes
   * in local space.
   *
   * @param x The angle, in radians, to rotate around the x axis.
   * @param y The angle, in radians, to rotate around the y axis.
   * @param z The angle, in radians, to rotate around the z axis.
   * @param order The order of the rotations.
   * @returns This 3D object.
   */
  Object3D &rotate(double x, double y, double z, EulerRotationOrder order) {
    this->localRotation.copy(this->localRotation +
                             EulerRotation(x, y, z, order));
    return *this;
  }

  /**
   * Scales this 3D object by the specified amounts along the x, y, and z axes
   * in local space.
   *
   * @param x The amount to scale along the x axis.
   * @param y The amount to scale along the y axis.
   * @param z The amount to scale along the z axis.
   * @returns This 3D object.
   */
  Object3D &scale(double x, double y, double z) {
    this->localScale *= Vector3(x, y, z);
    return *this;
  }

  // Vector3 getWorldPosition() const;
  // EulerRotation getWorldRotation() const;
  // Vector3 getWorldScale();

  /**
   * Updates the local transformation matrix of this 3D object.
   *
   * The local transformation matrix is calculated from the local position,
   * rotation, and scale of this 3D object.
   *
   * @returns This 3D object.
   */
  Object3D &updateLocalMatrix() {
    Matrix4x4 translationMatrix = Matrix4x4::fromTranslation(localPosition);
    Matrix4x4 rotationMatrix = Matrix4x4::fromRotation(localRotation);
    Matrix4x4 scaleMatrix = Matrix4x4::fromScale(localScale);

    localMatrix.copy(translationMatrix * rotationMatrix * scaleMatrix);
    return *this;
  }

  /**
   * Updates the model matrix of this 3D object.
   *
   * The model matrix is calculated as \f$M_pL\f$ where \f$M_p\f$ is the model
   * matrix of the parent of this 3D object and \f$L\f$ is the local matrix of
   * this 3D object. If this 3D object has no parent, the model matrix is the
   * same as the local matrix.
   *
   * @returns This 3D object.
   */
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