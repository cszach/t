#include "geometries/Geometry.hpp"
#include "materials/Material.hpp"
#include "primitives/Object3D.hpp"
#include <memory>

#ifndef MESH_HPP
#define MESH_HPP

namespace t {

class Mesh : public Object3D {
public:
  Geometry &geometry;
  Material &material;

  Mesh(Geometry &_geometry, Material &_material)
      : geometry(_geometry), material(_material) {};

  bool isMesh() const override { return true; }
};

} // namespace t

#endif // MESH_HPP