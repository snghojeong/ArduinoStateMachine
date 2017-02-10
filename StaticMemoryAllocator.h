#ifndef _MEMORY_ALLOCATOR_H_
#include "MemoryAllocator.h"
#endif

#ifndef _STATIC_MEMORY_ALLOCATOR_H_
#define _STATIC_MEMORY_ALLOCATOR_H_

template <size_t CSize>
class StaticMemoryAllocator : public MemoryAllocator {
private:
  uint8_t _buffer[CSize];
  size_t _length;

public:
  explicit StaticMemoryAllocator() : _length(0) {}

  inline size_t size() const {
    return CSize;
  }

  inline size_t length() const {
    return _length;
  }

  inline void* alloc(size_t bytes) {
    if (_length + bytes > CSize) return NULL;
    void* p = &_buffer[_length];
    _length += align(bytes);
    return p;
  }
};

#endif
