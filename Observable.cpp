#ifdef LINUX
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <time.h>
#include <math.h>
#else
#include <Arduino.h>
#endif

#include "Observable.h"
#include "Observer.h"
#include "Data.h"


Observable::Observable()
{
  _obsListIdx = 0;
  _dataListIdx = 0;
}

Observable::~Observable()
{
}

void Observable::subscribe(Observer* obs)
{
  _obsList[_obsListIdx++] = obs;
}

void Observable::push(Data* data)
{
  _dataList[_dataListIdx++] = data;
}

#ifdef LINUX
unsigned long Observable::millis() {
  unsigned long ret = 0;
  struct timespec spec;
  unsigned long ms;
  time_t s;

  clock_gettime(clock_realtime, &spec);

  s = spec.tv_sec;
  ms = round(spec.tv_nsec/1.0e6);

  ret = ((unsigned long)s * 1000) + ms;

  return ret;
}
#endif

bool Observable::setup()
{
  return true;
}

void Observable::loop()
{
  Data*     tmpDataList[MAX_ARR_SIZE_EVT];
  uint32_t  dataListLen;

  this->generateData();

  dataListLen = _dataListIdx;
  for (int i = 0; i < dataListLen; i++) {
    tmpDataList[i] = _dataList[i];
    _dataList[i] = NULL;
  }
  _dataListIdx = 0;

  for (int i = 0; i < dataListLen; i++) {
    for (int j = 0; j < _obsListIdx; j++) {
      _obsList[j]->notify(*(tmpDataList[i]));
    }
    delete tmpDataList[i]; // TODO: we need another way to release.
  }
}

