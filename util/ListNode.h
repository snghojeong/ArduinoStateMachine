#ifndef _MEMORY_ALLOCATOR_H_
#include "MemoryAllocator.h"
#endif

#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

template <typename T>
struct ListNode {
 public:
  ListNode() : next(NULL) {}

  void *operator new(size_t n, MemoryAllocator *allocator) throw() {
    if (!allocator) return NULL;
    return allocator->alloc(n);
  }

  void operator delete(void *, MemoryAllocator *) throw() {}

  ListNode<T> *next;
  T content;
};

#endif
