#include "Observable.h"


Observable::Observable()
{
  _obsListIdx = 0;
  _evtListIdx = 0;
}

Observable::~Observable()
{
}

void Observable::subscribe(Observer* obs)
{
  _obsList[_obsListIdx++] = obs;
}

void Observable::pushEvent(Event* evt)
{
  _evtList[_evtListIdx++] = evt;
}

bool Observable::setup()
{
}

void Observable::loop() // 1.gen evts 2.clone _evtList 3.process cloned _evtList 
{
  Event* tmpEvtList[MAX_ARR_SIZE_EVT];
  uint32_t evtListLen = _evtListIdx;

  this->generateEvents();

  for (int i = 0; i < evtListLen; i++) {
    tmpEvtList[i] = _evtList[i];
    _evtList[i] = NULL;
  }
  _evtListIdx = 0;

  for (int i = 0; i < _obsListIdx; i++) {
    for (int j = 0; j < evtListLen; j++) {
      _obsList[i]->notify(tmpEvtList[j]);
    }
  }
}

