#include <Arduino.h>

#include "StateElement.h"
#include "MemoryAllocator.h"

StateElement::StateElement()
: _eventList(NULL)
{
}

StateElement::StateElement(MemoryAllocator* allocator)
: _eventList(allocator)
{
}

StateElement::~StateElement()
{
}

EventElement* StateElement::getEvtElmt(const unsigned int key)
{
  ListIterator<EventElement> iter = _eventList.begin();
  while (iter != _eventList.end()) {
    EventElement& evt = *iter;
    if (evt == key) {
      return &evt;
    }
    ++iter;
  }
  return NULL;
}

EventElement& StateElement::operator[](const unsigned int key)
{
  EventElement* evt = this->getEvtElmt(key);
  if (evt != NULL) {
    return *evt;
  }

  // Not found
  ListNode<EventElement>* newEvtNode = _eventList.addNewNode();
  EventElement& newEvt = newEvtNode->content;

  return (newEvt = key);
}

