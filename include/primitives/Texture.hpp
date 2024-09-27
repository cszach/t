#include "constants.hpp"
#include <memory>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace t {

/**
 * The 2D texture class.
 *
 * A texture is an image that can be used for any purpose, such as a render
 * target, a texture map, a depth map, etc.
 */
template <class BufferType> class Texture {
public:
  int width;                     /**< The width of the texture in pixels. */
  int height;                    /**< The height of the texture in pixels. */
  TextureFormat format;          /**< The format of the texture. */
  std::vector<BufferType> image; /**< The image data of the texture. */

  /**
   * Creates a new texture with the given width, height, and format.
   */
  Texture(int _width, int _height, TextureFormat _format)
      : image(std::vector<BufferType>(_width * _height *
                                      static_cast<int>(_format))),
        width(_width), height(_height), format(_format) {}

  /**
   * Creates a new texture with the given image data, width, height, and format.
   *
   * @param _image The image data of the texture.
   * @param _width The width of the texture in pixels.
   * @param _height The height of the texture in pixels.
   * @param _format The format of the texture.
   */
  Texture(std::vector<BufferType> &_image, int _width, int _height,
          TextureFormat _format)
      : image(_image), width(_width), height(_height), format(_format) {}
};

} // namespace t

#endif // TEXTURE_HPP