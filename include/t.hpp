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
 * \addtogroup t
 * @{
 */

/**
 * The t software 3D graphics library.
 *
```cpp
#include "t.hpp"
```
 */
namespace t {}