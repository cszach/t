#include "t.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace t;

int main() {
  auto teapot = UtahTeapot();
  // auto material = NormalColor();
  auto material = BlinnPhong(Color(0, 0, 244), Color(255, 255, 255), 128);
  auto mesh = Mesh(teapot, material);

  auto ambient = AmbientLight(Color(64, 64, 64), 1);
  auto light = PointLight(Color(255, 255, 255), 1);
  light.translate(0, 1, 0);

  mesh.translate(0, -1.3, 0);

  const auto width = 80;
  const auto height = 24;
  const auto fwidth = static_cast<double>(width);
  const auto fheight = static_cast<double>(height);

  auto scene = Scene();
  auto camera = PerspectiveCamera(M_PI / 4, fwidth / fheight, 0.0001, 100);
  camera.translate(0, 0, 2.5);

  scene.add(ambient);
  scene.add(light);
  scene.add(mesh);
  scene.add(camera);

  auto renderer = Rasterizer();
  auto renderTarget =
      RenderTarget<double>(width, height, TextureFormat::RgbDouble);

  const auto characters = std::array<char, 12>{'.', ',', '-', '~', ':', ';',
                                               '=', '!', '*', '#', '$', '@'};

  auto startTime = std::chrono::high_resolution_clock::now();
  long lastRenderTimestamp = 0;

  while (true) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                         currentTime - startTime)
                         .count();
    std::cout << "\x1b[H";

    if (elapsedMs > 0) {
      std::cout << "FPS: " << std::setfill(' ') << std::setw(3)
                << 1000 / (elapsedMs - lastRenderTimestamp);
    }

    // mesh.localRotation.y = 0.001 * elapsedMs;
    light.localPosition.x = cos(0.001 * elapsedMs) * 2;
    light.localPosition.z = sin(0.001 * elapsedMs) * 2;

    lastRenderTimestamp = elapsedMs;

    renderer.render(scene, camera, renderTarget);

    for (int j = 0; j < renderTarget.height; j++) {
      for (int i = renderTarget.width - 1; i > -1; i--) {
        if (j == 0 && i > renderTarget.width - 8) {
          continue;
        }

        int index = (i + j * renderTarget.width) * 3;

        auto r = renderTarget.texture.image[index];
        auto g = renderTarget.texture.image[index + 1];
        auto b = renderTarget.texture.image[index + 2];

        const auto luminance = t::Color(r, g, b).luminance();

        r = std::clamp(r, 0.0, 1.0);
        g = std::clamp(g, 0.0, 1.0);
        b = std::clamp(b, 0.0, 1.0);

        char c = ' ';

        for (int cs = 11; cs > -1; cs--) {
          if ((1.0 / 12) * cs < luminance) {
            c = characters[cs];
            break;
          }
        }

        std::cout << "\033[38;2;" << static_cast<int>(r * 255) << ";"
                  << static_cast<int>(g * 255) << ";"
                  << static_cast<int>(b * 255) << "m" << c << "\033[0m";
      }

      if (j < renderTarget.height - 1) {
        std::cout << "\n";
      }
    }
  }

  return 0;
}