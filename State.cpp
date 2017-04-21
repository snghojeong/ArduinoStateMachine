#include <Arduino.h>

#include "State.h"
#include "Event.h"

State::State()
{
  _evtListIdx = 0;
  _duringProc = NULL;

  for (int i = 0; i < MAX_ARR_SIZE_STS_EVT; i++) {
    _evtList[i] = NULL;
    _evtProcList[i] = NULL;
    _nextState[i] = NULL;
  }
}

State::~State()
{
}

void State::registerEvent(Event* evt, EventProcedure* evtProc, State* nextState)
{
  if (_evtListIdx < MAX_ARR_SIZE_STS_EVT) {
    _evtList[_evtListIdx] = evt;
    _evtProcList[_evtListIdx] = evtProc;
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
      (*_evtProcList[i])();
      return _nextState[i];
    }
  }
  return NULL;
}

