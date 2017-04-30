#include <Arduino.h>

#include "State.h"
#include "Event.h"

State::State(StateMachine& owner)
: _owner(owner)
{
  _evtListIdx = 0;
  _duringLambda = NULL;

  for (int i = 0; i < MAX_ARR_SIZE_STS_EVT; i++) {
    _evtList[i] = NULL;
    _evtProcLambda[i] = NULL;
    _nextState[i] = NULL;
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

State* State::processEvent(Event* evt)
{
  for (int i = 0; i < _evtListIdx; i++) {
    if ((*_evtList[i]) == (*evt)) {
      (_evtProcLambda[i])(_owner);
      return _nextState[i];
    }
  }
  return NULL;
}

