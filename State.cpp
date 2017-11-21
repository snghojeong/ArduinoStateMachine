#ifdef LINUX
#include <cstddef>
#include <cstdint>
#include <cstring>
#else
#include <Arduino.h>
#endif

#include "State.h"
#include "Event.h"

State::State(StateMachine& owner)
: _owner(owner)
{
  _evtListIdx = 0;
  _duringLambda = nullptr;

  for (int i = 0; i < MAX_ARR_SIZE_STS_EVT; i++) {
    _evtList[i] = nullptr;
    _evtProcLambda[i] = nullptr;
    _nextState[i] = nullptr;
  }
}

State::~State()
{
}

void State::registerEvent(Event* evt, State* nextState, void (*evtProcLambda)(StateMachine& stateMachine))
{
  if (_evtListIdx < MAX_ARR_SIZE_STS_EVT) {
    _evtList[_evtListIdx] = evt;
    _evtProcLambda[_evtListIdx] = evtProcLambda;
    _nextState[_evtListIdx] = nextState;
    _evtListIdx++;
  } else {
    return; // TODO: Error handling.
  }
}

State* State::processEvent(Event& evt)
{
  for (int i = 0; i < _evtListIdx; i++) {
    if ((*_evtList[i]) == evt) {
      (_evtProcLambda[i])(_owner);
      return _nextState[i];
    }
  }
  return nullptr;
}

