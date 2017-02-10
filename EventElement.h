#ifndef _EVENT_PROCEDURE_INTERFACE_H_
#include "EventProcedureInterface.h"
#endif

#ifndef _EVENT_ELEMENT_H_
#define _EVENT_ELEMENT_H_

class StateMachineComponent;

class EventElement {
private:
  EventProcedureInterface* _eventProc;
  unsigned int _nextState;
  unsigned int _key;

public:
  explicit EventElement() : _eventProc(NULL) {}
  virtual ~EventElement() {}
  EventProcedureInterface* getEvtProc() { return _eventProc; }
  unsigned int getNextState() { return _nextState; }
  EventElement& operator<<(EventProcedureInterface* eventProc) { _eventProc = eventProc; return *this; }
  EventElement& operator<<(const unsigned int nextState) { _nextState = nextState; return *this; }
  bool operator==(const unsigned int key) const { return (_key == key); }
  EventElement& operator=(const unsigned int key) { _key = key; return *this; }
  unsigned int operator()(StateMachineComponent& stateMachine) { return (*_eventProc)(stateMachine); }
};

#endif
