#include <initializer_list>
#include <span>
#include <vector>

#ifndef BUFFERATTRIBUTE_HPP
#define BUFFERATTRIBUTE_HPP

namespace t {

template <class BufferType> class BufferAttribute {
public:
  std::vector<BufferType> array;
  int itemSize;

  BufferAttribute(std::initializer_list<BufferType> _array, int _itemSize)
      : array(_array), itemSize(_itemSize) {}
};

} // namespace t

#endif // BUFFERATTRIBUTE_HPP