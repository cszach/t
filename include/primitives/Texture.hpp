#include "constants.hpp"
#include <memory>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace t {

template <class BufferType> class Texture {
public:
  int width;
  int height;
  TextureFormat format;
  std::vector<BufferType> image;

  Texture(int _width, int _height, TextureFormat _format)
      : image(std::vector<BufferType>(_width * _height *
                                      static_cast<int>(_format))),
        width(_width), height(_height), format(_format) {}

  Texture(std::vector<BufferType> &_image, int _width, int _height,
          TextureFormat _format)
      : image(_image), width(_width), height(_height), format(_format) {}
};

} // namespace t

#endif // TEXTURE_HPP