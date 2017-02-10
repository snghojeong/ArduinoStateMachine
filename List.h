#ifndef _LIST_NODE_H_
#include "ListNode.h"
#endif

#ifndef _LIST_ITERATOR_H_
#include "ListIterator.h"
#endif

#ifndef _LIST_CONST_ITERATOR_H_
#include "ListConstIterator.h"
#endif

#ifndef _LIST_H_
#define _LIST_H_

template <typename T>
class List {
 public:
  typedef T value_type;
  typedef ListNode<T> node_type;
  typedef ListIterator<T> iterator;
  typedef ListConstIterator<T> const_iterator;

  explicit List(MemoryAllocator* allocator) : _buffer(allocator), _firstNode(NULL) {}

  void setBuffer(MemoryAllocator* allocator) { _buffer = allocator; }

  bool success() const {
    return _buffer != NULL;
  }

  size_t size() const {
    size_t nodeCount = 0;
    for (node_type *node = _firstNode; node; node = node->next) nodeCount++;
    return nodeCount;
  }

  iterator begin() {
    return iterator(_firstNode);
  }
  iterator end() {
    return iterator(NULL);
  }

  const_iterator begin() const {
    return const_iterator(_firstNode);
  }
  const_iterator end() const {
    return const_iterator(NULL);
  }
  
  node_type *addNewNode() {
    node_type *newNode = new (_buffer) node_type();

    if (_firstNode) {
      node_type *lastNode = _firstNode;
      while (lastNode->next) lastNode = lastNode->next;
      lastNode->next = newNode;
    } else {
      _firstNode = newNode;
    }

    return newNode;
  }

  void removeNode(node_type *nodeToRemove) {
    if (!nodeToRemove) return;
    if (nodeToRemove == _firstNode) {
      _firstNode = nodeToRemove->next;
    } else {
      for (node_type *node = _firstNode; node; node = node->next)
        if (node->next == nodeToRemove) node->next = nodeToRemove->next;
    }
  }
  
protected:
  MemoryAllocator* _buffer;
  node_type *_firstNode;
};

#endif
