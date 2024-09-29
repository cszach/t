# t

A software graphics library written in C++, originally for the terminal.

![A GIF of a rotating teapot in the terminal](img/teapot.gif)

_Rendering the original Utah teapot (triangulated at 3488 tris) in 125 FPS._

## Example

The below example creates a cube with its normals mapped to its colors, then
animate it rotating in a while loop. The cube's rotational speed might be
slightly different depending on your CPU.

```cpp
#include "t.hpp"
#include <iostream>

using namespace t;

int main() {
  auto box = Box(1, 1, 1);
  auto material = NormalColor();
  auto mesh = Mesh(box, material);

  const auto width = 80;
  const auto height = 24;

  auto scene = Scene();
  auto camera = PerspectiveCamera(M_PI / 4, static_cast<double>(width) / height,
                                  0.01, 10);
  camera.translate(0, 0, 1);

  scene.add(mesh);
  scene.add(camera);

  auto renderer = Rasterizer();
  auto renderTarget =
      RenderTarget<double>(width, height, TextureFormat::RgbDouble);

  while (true) {
    mesh.localRotation.x += 0.002;
    mesh.localRotation.y += 0.001;

    renderer.render(scene, camera, renderTarget);

    std::cout << "\x1b[H"; // Set terminal's cursor position to top-left corner

    for (int j = 0; j < renderTarget.height; j++) {
      for (int i = renderTarget.width - 1; i > -1; i--) {
        int index = (i + j * renderTarget.width) * 3;

        auto r = renderTarget.texture.image[index];
        auto g = renderTarget.texture.image[index + 1];
        auto b = renderTarget.texture.image[index + 2];

        std::cout << "\033[38;2;" << static_cast<int>(r * 255) << ";"
                  << static_cast<int>(g * 255) << ";"
                  << static_cast<int>(b * 255) << "m@\033[0m";
      }

      std::cout << "\n";
    }
  }
}
```

## Getting started

Clone:

```
git clone https://github.com/cszach/t.git
```

Compile:

```
cmake -B build .
cmake --build build
```

Run:

```
cd build/bin
./cube
```

Test:

```
cd build
ctest
```

## Demos

- [`cube.cpp`](src/cube.cpp): the rotating cube example from above,
- [`cornell_box.cpp`](src/cornell_box.cpp): the classic Cornell box rendered
  with Blinn-Phong shading,
- [`teapot.cpp`](src/teapot.cpp): a spinning animation of the triangulated
  original Utah teapot (3488 tris) with normal material, with an FPS counter at
  the top-left (might not be visible due to the output being constantly
  overwritten); useful for testing performance.
- [`triangle.cpp`](src/triangle.cpp): a simple triangle printed to the terminal
  screen. Demonstrates how to set up a custom 3D geometry.

For all demos, please make sure your terminal is at least 80 cells wide and 24
cells high. You can go into the source code and change the `width` and `height`
values.

## Specification

### Primitives

- Right-handed coordinate system
  - Positive Y is up.
  - Z for depth. Positive Z is generally considered "towards the viewer".
- Each `Mesh` has a shape (geometry) and a look (material).
- An `Object3D` is either a `Mesh`, a `Scene`, or a group of any `Object3D`, and
  has a local position, rotation, and scale.
- The vertex data maybe indexed or not.

### Math

- Matrix-vector multiplication use post-multiplication notation.
  - That means `B = MA` where `M` is a matrix, and `A` and `B` are vectors.
- Like WebGL, matrix addition, subtraction, and division are component-wise,
  but multiplication is not.

### Renderers

#### Rasterizer

- Forward rendering pipeline with vertex and fragment shading.
- One "draw call" for every mesh.

## 🚧 To-do's

- Directional light
- Spot light
- Shadows
- OBJ import
- Post-processing
- Better name?

### Fix-me's

- The camera's `lookAt`'s target is currently hard-coded to the zero vector.
- The x-axis in the render target appears to be flipped.
- Camera's near and far values are currently ignored.

### Will not be worked on

I will focus my time and efforts on another renderer, but here are some ideas
for potential contributors. Feel free to tell me about your forks.

- Alpha color
- Color blending
- Quaternions
- Stencil buffer
- SIMD
- Image textures
- More geometries
- More materials
- UVs
- Deferred rendering
- Parallel computing
- Ray tracing
- Wider ASCII character set
- Interactive 3D in the terminal demo
- More coverage for unit tests
- Robust Euler rotation computations
- Custom varyings

## 🙌 Acknowledgements

API design is inspired by [three.js](https://threejs.org).

The rendering pipeline is inspired by WebGL and WebGPU.
