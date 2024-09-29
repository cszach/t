#include "Object3D.hpp"
#include <memory>
#include <vector>

#ifndef SCENE_HPP
#define SCENE_HPP

namespace t {

/**
 * The 3D scene class.
 *
 * The scene is the container for all 3D objects in a scene. In the 3D scene
 * graph, the scene is the root node.
 *
 * \ingroup primitives
 */
class Scene : public Object3D {};

} // namespace t

#endif // SCENE_HPP