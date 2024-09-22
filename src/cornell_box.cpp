#include "t.hpp"
#include <iostream>

using namespace t;

int main() {
  auto plane = Plane(1, 1);
  auto black = Color(0, 0, 0);
  auto red = Color(180, 0, 0);
  auto green = Color(0, 180, 0);
  auto white = Color(180, 180, 180);

  auto leftWallMaterial = BlinnPhong(red, black, 0);
  auto leftWall = Mesh(plane, leftWallMaterial);
  leftWall.translate(-0.5, 0, 0);
  leftWall.rotate(0, M_PI / 2, 0, EulerRotationOrder::Xyz);

  auto rightWallMaterial = BlinnPhong(green, black, 0);
  auto rightWall = Mesh(plane, rightWallMaterial);
  rightWall.translate(0.5, 0, 0);
  rightWall.rotate(0, -M_PI / 2, 0, EulerRotationOrder::Xyz);

  auto whiteMaterial = BlinnPhong(white, black, 0);

  auto backWall = Mesh(plane, whiteMaterial);
  backWall.translate(0, 0, -0.5);

  auto ground = Mesh(plane, whiteMaterial);
  ground.translate(0, -0.5, 0);
  ground.rotate(-M_PI / 2, 0, 0, EulerRotationOrder::Xyz);

  auto ceiling = Mesh(plane, whiteMaterial);
  ceiling.translate(0, 0.5, 0);
  ceiling.rotate(M_PI / 2, 0, 0, EulerRotationOrder::Xyz);

  auto box = Box(0.3, 0.3, 0.3);
  auto boxTestMaterial = SolidColor(Color(255, 0, 255));

  auto tallBox = Mesh(box, whiteMaterial);
  tallBox.translate(-0.25, -0.2, -0.25);
  tallBox.scale(1, 2, 1);
  tallBox.rotate(0, M_PI / 10, 0, EulerRotationOrder::Xyz);

  auto shortBox = Mesh(box, whiteMaterial);
  shortBox.translate(0.2, -0.35, 0.25);
  shortBox.rotate(0, -M_PI / 10, 0, EulerRotationOrder::Xyz);

  auto ambient = AmbientLight(Color(255, 255, 255), 1);
  auto light = PointLight(Color(255, 255, 255), 1);
  light.translate(0, 0.5, 0);

  auto lightGeometry = Plane(0.2, 0.2);
  auto lightMaterial = SolidColor(Color(255, 255, 255));
  auto lightMesh = Mesh(lightGeometry, lightMaterial);

  lightMesh.translate(0, 0.499, 0);
  lightMesh.rotate(M_PI / 2, 0, 0, EulerRotationOrder::Xyz);

  const auto width = 80;
  const auto height = 24;
  const auto fwidth = static_cast<double>(width);
  const auto fheight = static_cast<double>(height);

  auto scene = Scene();
  auto camera = PerspectiveCamera(M_PI / 4, fwidth / fheight, 0.0001, 100);
  camera.translate(0, 0, 1);

  scene.add(leftWall);
  scene.add(rightWall);
  scene.add(backWall);
  scene.add(ground);
  scene.add(ceiling);
  scene.add(tallBox);
  scene.add(shortBox);
  scene.add(ambient);
  scene.add(light);
  scene.add(lightMesh);
  scene.add(camera);

  auto renderer = Rasterizer();
  auto renderTarget =
      RenderTarget<double>(width, height, TextureFormat::RgbDouble);

  renderer.render(scene, camera, renderTarget);

  const auto characters = std::array<char, 12>{'.', ',', '-', '~', ':', ';',
                                               '=', '!', '*', '#', '$', '@'};

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

      char c = ' ';

      for (int cs = 11; cs > -1; cs--) {
        if ((1.0 / 12) * cs < luminance) {
          c = characters[cs];
          break;
        }
      }

      std::cout << "\033[38;2;" << static_cast<int>(r * 255) << ";"
                << static_cast<int>(g * 255) << ";" << static_cast<int>(b * 255)
                << "m" << c << "\033[0m";
    }

    std::cout << std::endl;
  }
}