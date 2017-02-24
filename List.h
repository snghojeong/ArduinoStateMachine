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
  explicit List(MemoryAllocator* allocator) : _buffer(allocator), _firstNode(NULL) {}

  void setBuffer(MemoryAllocator* allocator) { _buffer = allocator; }

  size_t size() const {
    size_t nodeCount = 0;
    for (ListNode<T> *node = _firstNode; node; node = node->next) nodeCount++;
    return nodeCount;
  }

  ListIterator<T> begin() {
    return ListIterator<T>(_firstNode);
  }
  ListIterator<T> end() {
    return ListIterator<T>(NULL);
  }

  ListConstIterator<T> begin() const {
    return ListConstIterator<T>(_firstNode);
  }
  ListConstIterator<T> end() const {
    return ListConstIterator<T>(NULL);
  }
  
  ListNode<T> *addNewNode() {
    ListNode<T> *newNode = new (_buffer) ListNode<T>();

    if (_firstNode) {
      ListNode<T> *lastNode = _firstNode;
      while (lastNode->next) lastNode = lastNode->next;
      lastNode->next = newNode;
    } else {
      _firstNode = newNode;
    }

    return newNode;
  }

  void removeNode(ListNode<T> *nodeToRemove) {
    if (!nodeToRemove) return;
    if (nodeToRemove == _firstNode) {
      _firstNode = nodeToRemove->next;
    } else {
      for (ListNode<T> *node = _firstNode; node; node = node->next)
        if (node->next == nodeToRemove) node->next = nodeToRemove->next;
    }
  }
  
protected:
  MemoryAllocator* _buffer;
  ListNode<T> *_firstNode;
};

#endif
