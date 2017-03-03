#ifndef _MEMORY_ALLOCATOR_H_
#define _MEMORY_ALLOCATOR_H_

class MemoryAllocator {
public:
  virtual size_t size() const = 0;
  virtual size_t length() const = 0;
  virtual void* alloc(size_t bytes) = 0;

protected:
  inline size_t align(size_t bytes) {
    const size_t x = sizeof(void *) - 1;
    return (bytes + x) & ~x;
  }
};

#endif
