#include "math/Matrix3x3.hpp"
#include "math/Matrix4x4.hpp"
#include "math/Vector3.hpp"

#ifndef UNIFORMS_HPP
#define UNIFORMS_HPP

namespace t {

/**
 * The uniforms available to {@linkplain Material#vertexShader vertex shaders}
 * and {@linkplain Material#fragmentShader fragment shaders}.
 *
 * Uniforms are values that are constant for all vertices and fragments in a
 * single draw call.
 */
struct Uniforms {
  Matrix4x4 &modelMatrix;     /**< The model matrix of the current 3D mesh. */
  Matrix4x4 &modelViewMatrix; /**< The product of the view matrix and the model
                                 matrix. */
  Matrix4x4
      &projectionMatrix;   /**< The projection matrix of the active camera. */
  Matrix4x4 &viewMatrix;   /**< The view matrix of the active camera. */
  Matrix3x3 &normalMatrix; /**< The normal matrix of the current 3D mesh. */
  Vector3 &cameraPosition; /**< The position of the camera in world space. */
};

} // namespace t

#endif // UNIFORMS_HPP