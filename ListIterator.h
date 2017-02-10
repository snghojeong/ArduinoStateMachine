#ifndef _LIST_ITERATOR_H_
#define _LIST_ITERATOR_H_

// A read-write forward iterator for List<T>
template <typename T>
class ListIterator {
 public:
  explicit ListIterator(ListNode<T> *node = NULL) : _node(node) {}

  T &operator*() const { return _node->content; }
  T *operator->() { return &_node->content; }

  bool operator==(const ListIterator<T> &other) const {
    return _node == other._node;
  }

  bool operator!=(const ListIterator<T> &other) const {
    return _node != other._node;
  }

  ListIterator<T> &operator++() {
    if (_node) _node = _node->next;
    return *this;
  }

  //operator ListConstIterator<T>() const { return ListConstIterator<T>(_node); }

 private:
  ListNode<T> *_node;
};

#endif
