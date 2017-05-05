#ifndef _COMPONENT_INTERFACE_H_
#include "ComponentInterface.h"
#endif

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#define MAX_ARR_SIZE_OBS  8
#define MAX_ARR_SIZE_EVT  16

class Observer;
class Event;

class Observable : public ComponentInterface {
private:
  Observer* _obsList[MAX_ARR_SIZE_OBS];
  uint32_t  _obsListIdx;
  Event*    _evtList[MAX_ARR_SIZE_EVT];
  uint8_t*  _dataList[MAX_ARR_SIZE_EVT];
  size_t    _dataLenList[MAX_ARR_SIZE_EVT];
  uint32_t  _evtDataListIdx;

public:
  explicit Observable();
  virtual ~Observable();
  void subscribe(Observer* obs);
  void pushEvent(Event* evt, uint8_t* data = nullptr, size_t len = 0);

protected:
  uint32_t getEvtListLen() const { return _evtDataListIdx; }
  virtual void generateEvents() = 0;

  // Override ComponentInterface
public:
  virtual bool setup();
  virtual void loop();

  virtual uint32_t getPeriod() const = 0;
};

#endif
