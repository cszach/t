#include "t.hpp"
#include <iostream>

using namespace t;

int main() {
  auto vertexPositions =
      BufferAttribute<double>({0, 1, 0, -1, 0, 0, 1, 0, 0}, 3);
  auto vertexNormals = BufferAttribute<double>({0, 0, 1, 0, 0, 1, 0, 0, 1}, 3);

  auto geometry = Geometry(vertexPositions, vertexNormals);
  auto material = NormalColor();
  auto mesh = Mesh(geometry, material);

  auto width = 80.0;
  auto height = 24.0;

  auto scene = Scene();
  auto camera = OrthographicCamera(-width / 2, width / 2, height / 2,
                                   -height / 2, 0.1, 2000);
  auto renderTarget =
      RenderTarget<double>(width, height, TextureFormat::RgbDouble);
  auto renderer = Rasterizer();

  mesh.scale(10, 10, 10);
  mesh.translate(0, -5, 0);
  scene.add(mesh);
  scene.add(camera);
  camera.translate(0, 0, 1);
  renderer.render(scene, camera, renderTarget);

  for (int j = 0; j < renderTarget.height; j++) {
    for (int i = renderTarget.width - 1; i > -1; i--) {
      int index = (i + j * renderTarget.width) * 3;

      auto r = renderTarget.texture.image[index];
      auto g = renderTarget.texture.image[index + 1];
      auto b = renderTarget.texture.image[index + 2];

      const auto luminance = t::Color(r, g, b).luminance();

      r = std::clamp(r, 0.0, 1.0);
      g = std::clamp(g, 0.0, 1.0);
      b = std::clamp(b, 0.0, 1.0);

      std::cout << "\033[38;2;" << static_cast<int>(r * 255) << ";"
                << static_cast<int>(g * 255) << ";" << static_cast<int>(b * 255)
                << "m@\033[0m";
    }

    std::cout << std::endl;
  }
}