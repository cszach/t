#include "primitives/Object3D.hpp"

#ifndef LIGHT_HPP
#define LIGHT_HPP

namespace t {

/**
 * The base lighting class.
 *
 * This class should not be used directly. Use a {@link PointLight} or
 * {@link AmbientLight} instead, or create your own light by deriving from this
 * class.
 *
 * \ingroup lights
 */
class Light : public Object3D {
public:
  /**
   * Returns whether or not this 3D object is a light.
   *
   * Always returns `true`. Used in the renderer to separate lights from other
   * 3D objects.
   *
   * @returns `true`
   */
  bool isLight() const override { return true; }

  /**
   * Returns whether or not this light is an ambient light.
   *
   * Always returns `false`. This value will be overridden by the {@link
   * AmbientLight} class.
   *
   * @returns `false`
   */
  virtual bool isAmbientLight() const { return false; }

  /**
   * Returns whether or not this light is a point light.
   *
   * Always returns `false`. This value will be overridden by the {@link
   * PointLight} class.
   *
   * @returns `false`
   */
  virtual bool isPointLight() const { return false; }

  /**
   * Returns whether or not this light is a directional light.
   *
   * Always returns `false`.
   *
   * @returns `false`
   */
  virtual bool isDirectionalLight() const { return false; }

  /**
   * Returns whether or not this light is a spot light.
   *
   * Always returns `false`.
   *
   * @returns `false`
   */
  virtual bool isSpotLight() const { return false; }
};

} // namespace t

#endif // LIGHT_HPP