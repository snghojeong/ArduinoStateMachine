#include <Arduino.h>

#include "StateMachine.h"


Event StateMachine::_during;


StateMachine::StateMachine(State* initState)
: _currState(initState)
{
  this->subscribe(this);
}

StateMachine::~StateMachine()
{
}

void StateMachine::generateEvents()
{
  if (this->getEvtListLen() == 0) {
    this->pushEvent(&_during, nullptr, 0);
  }
}

void StateMachine::notify(Event* evt, uint8_t* data, size_t dataLen)
{
  if ((*evt) == _during) {
    _currState->during();
  } else {
    State* nextState = _currState->processEvent(evt, data, dataLen);
    if (nextState != NULL) {
      _currState = nextState;
    }
  }
}

