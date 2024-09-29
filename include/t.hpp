#include "algorithms.hpp"
#include "cameras/Camera.hpp"
#include "cameras/OrthographicCamera.hpp"
#include "cameras/PerspectiveCamera.hpp"
#include "constants.hpp"
#include "geometries/Box.hpp"
#include "geometries/Geometry.hpp"
#include "geometries/Plane.hpp"
#include "geometries/UtahTeapot.hpp"
#include "lights/AmbientLight.hpp"
#include "lights/Light.hpp"
#include "lights/PointLight.hpp"
#include "materials/BlinnPhong.hpp"
#include "materials/Material.hpp"
#include "materials/NormalColor.hpp"
#include "materials/SolidColor.hpp"
#include "math/EulerRotation.hpp"
#include "math/Matrix3x3.hpp"
#include "math/Matrix4x4.hpp"
#include "math/Vector3.hpp"
#include "math/Vector4.hpp"
#include "primitives/Attributes.hpp"
#include "primitives/BufferAttribute.hpp"
#include "primitives/Color.hpp"
#include "primitives/Fragment.hpp"
#include "primitives/Mesh.hpp"
#include "primitives/Object3D.hpp"
#include "primitives/RenderTarget.hpp"
#include "primitives/Scene.hpp"
#include "primitives/Texture.hpp"
#include "primitives/Uniforms.hpp"
#include "primitives/Varyings.hpp"
#include "renderers/Rasterizer.hpp"

/**
 * @defgroup cameras
 * 
 * A camera is a point of view in a 3D scene. It is defined by a projection
 * matrix that transforms the view-space coordinates into normalized device
 * coordinates (NDC).
 */
/**
 * @defgroup geometries
 * 
 * A geometry defines the shape of a 3D object. It includes information such as
 * the positions of the vertices, the normals of the vertices, and the indices
 * of the vertices that make up the faces.
 */
/**
 * @defgroup lights
 * 
 * Lights illuminate 3D objects in a scene.
 */
/**
 * @defgroup materials
 * 
 * Materials define the look of 3D objects.
 */
/**
 * @defgroup math
 * 
 * Common mathematical operations and utilities used in 3D graphics.
 */
/**
 * @defgroup primitives
 * 
 * The basic building blocks of 3D graphics such as colors, objects, textures,
 * shader inputs, and more.
 */
/**
 * @defgroup renderers
 * 
 * A renderer transforms a 3D scene into a 2D image from the point of view of
 * the active camera.
 */

/**
 * The t software 3D graphics library namespace.
 *
```cpp
#include "t.hpp"
```
 */
namespace t {}