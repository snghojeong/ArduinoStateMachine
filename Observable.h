#ifndef _COMPONENT_INTERFACE_H_
#include "ComponentInterface.h"
#endif

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#define MAX_ARR_SIZE_OBS  8
#define MAX_ARR_SIZE_EVT  16

class Observer;
class Data;

class Observable : public ComponentInterface {
private:
  Observer* _obsList[MAX_ARR_SIZE_OBS];
  uint32_t  _obsListIdx;
  Data*     _dataList[MAX_ARR_SIZE_EVT];
  uint32_t  _dataListIdx;

public:
  explicit Observable();
  virtual ~Observable();
  void subscribe(Observer* obs);

protected:
  void push(Data* data);
  uint32_t getDataListLen() const { return _dataListIdx; }
  Data& getData(uint32_t idx) const { return *(_dataList[idx]); }
  virtual void generateData() = 0;
#ifdef LINUX
  unsigned long millis();
#endif

  // Override ComponentInterface
public:
  virtual bool setup();
  virtual void loop();

  virtual uint32_t getPeriod() const = 0;
};

#endif
