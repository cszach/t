#include "primitives/Texture.hpp"

#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

namespace t {

template <typename BufferType> class RenderTarget {
public:
  int width;
  int height;
  Texture<BufferType> texture;

  RenderTarget(int _width, int _height, TextureFormat _format)
      : width(_width), height(_height), texture(_width, _height, _format) {}

  Color read(int x, int y) {
    switch (this->texture.format) {
    case TextureFormat::RgbDouble:
      return Color(texture.image[x * 3 + y * width * 3],
                   texture.image[x * 3 + y * width * 3 + 1],
                   texture.image[x * 3 + y * width * 3 + 2]);

    case TextureFormat::Depth:
      const auto depth = texture.image[x + y * width];
      return Color(depth, depth, depth);
    }

    return Color(0, 0, 0);
  }

  void write(int x, int y, Color color) {
    switch (this->texture.format) {
    case TextureFormat::RgbDouble:
      texture.image[x * 3 + y * width * 3] = color.x;
      texture.image[x * 3 + y * width * 3 + 1] = color.y;
      texture.image[x * 3 + y * width * 3 + 2] = color.z;
      break;

    case TextureFormat::Depth:
      texture.image[x + y * width] = color.x;
      break;
    }
  }
};

} // namespace t

#endif // RENDERTARGET_HPP