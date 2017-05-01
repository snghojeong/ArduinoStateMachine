#include <Arduino.h>

#include "Observable.h"
#include "Observer.h"


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

void Observable::pushEvent(Event* evt, uint8_t* data, size_t dataLen)
{
  _evtList[_evtListIdx] = evt;
  _dataList[_evtListIdx] = data;
  _dataLenList[_evtListIdx] = dataLen;
  ++_evtListIdx;
}

bool Observable::setup()
{
  return true;
}

void Observable::loop()
{
  Event*    tmpEvtList[MAX_ARR_SIZE_EVT];
  uint8_t*  tmpDataList[MAX_ARR_SIZE_EVT];
  size_t    tmpDataLenList[MAX_ARR_SIZE_EVT];
  uint32_t  evtListLen;

  this->generateEvents();

  evtListLen = _evtListIdx;
  for (int i = 0; i < evtListLen; i++) {
    tmpEvtList[i] = _evtList[i];
    tmpDataList[i] = _dataList[i];
    tmpDataLenList[i] = _dataLenList[i];
    _evtList[i] = NULL;
  }
  _evtListIdx = 0;

  for (int i = 0; i < _obsListIdx; i++) {
    for (int j = 0; j < evtListLen; j++) {
      _obsList[i]->notify(tmpEvtList[j], tmpDataList[i], tmpDataLenList[i]);
    }
  }
}

