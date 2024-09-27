#include "geometries/Geometry.hpp"
#include "materials/Material.hpp"
#include "primitives/Object3D.hpp"
#include <memory>

#ifndef MESH_HPP
#define MESH_HPP

namespace t {

/**
 * The triangular 3D mesh class.
 *
 * A mesh has a shape (geometry) and a look (material).
 */
class Mesh : public Object3D {
public:
  Geometry &geometry; /**< The geometry of this mesh. */
  Material &material; /**< The material of this mesh. */

  /**
   * Creates a new mesh with the specified geometry and material.
   *
   * @param _geometry The geometry of the mesh.
   * @param _material The material of the mesh.
   */
  Mesh(Geometry &_geometry, Material &_material)
      : geometry(_geometry), material(_material) {};

  /**
   * Returns whether this 3D object is a mesh.
   *
   * Used internally for type checking before casting an {@link Object3D} to a
   * {@link Mesh}.
   */
  bool isMesh() const override { return true; }
};

} // namespace t

#endif // MESH_HPP