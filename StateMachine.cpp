#ifdef LINUX
#include <cstddef>
#include <cstdint>
#include <cstring>
#else
#include <Arduino.h>
#endif

#include "StateMachine.h"
#include "Data.h"


StateMachine::StateMachine(State* initState)
: _currState(initState)
{
  this->subscribe(this);
}

StateMachine::~StateMachine()
{
}

void StateMachine::pushEvent(Event* evt)
{
  Data* data = new Data(sizeof(uint32_t)); // TODO: Data& data = CircularQueue<Data>::alloc();
  evt->serialize(*data);
  this->push(data);
}

void StateMachine::generateData()
{
  uint16_t evtCnt = 0;

  for (int i = 0; i < this->getDataListLen(); i++) {
    Data& data = this->getData(i);
    if (data.type() == Event::_evtDataType) {
      evtCnt++;
      break;
    }
  }

  if (evtCnt == 0) {
    _currState->during();
  }
}

void StateMachine::notify(Data& data)
{
  if (data.type() == Event::_evtDataType) {
    Event evt(data);
    State* nextState = _currState->processEvent(evt);
    if (nextState != nullptr) {
      _currState = nextState;
    }
  }
}

