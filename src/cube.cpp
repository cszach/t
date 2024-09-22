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