#include "primitives/Object3D.hpp"

#ifndef LIGHT_HPP
#define LIGHT_HPP

namespace t {

class Light : public Object3D {
public:
  bool isLight() const override { return true; }
  virtual bool isAmbientLight() const { return false; }
  virtual bool isPointLight() const { return false; }
  virtual bool isDirectionalLight() const { return false; }
  virtual bool isSpotLight() const { return false; }
};

} // namespace t

#endif // LIGHT_HPP