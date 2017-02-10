#ifndef _LIST_H_
#include "List.h"
#endif

#ifndef _EVENT_ELEMENT_H_
#include "EventElement.h"
#endif

#ifndef _STATE_ELEMENT_H_
#define _STATE_ELEMENT_H_

class MemoryAllocator;

class StateElement {
private:
  List<EventElement> _eventList;
  unsigned int _key;

public:
  explicit StateElement();
  explicit StateElement(MemoryAllocator* allocator);
  virtual ~StateElement();

  void setMemAllocator(MemoryAllocator* allocator) { _eventList.setBuffer(allocator); }
  EventElement* getEvtElmt(const unsigned int key);

  EventElement& operator[](const unsigned int key);
  bool operator==(const unsigned int key) const { return (_key == key); }
  StateElement& operator=(const unsigned int key) { _key = key; return *this; }
};

#endif
