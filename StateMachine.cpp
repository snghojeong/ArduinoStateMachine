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
    this->pushEvent(&_during);
  }
}

void StateMachine::notify(Event* evt)
{
  if ((*evt) == _during) {
    _currState->during();
  } else {
    State* nextState = _currState->processEvent(evt);
    if (nextState != NULL) {
      _currState = nextState;
    } else {
      _currState->during();
    }
  }
}

