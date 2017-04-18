#ifndef _COMPONENT_INTERFACE_H_
#include <ComponentInterface.h>
#endif

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#define MAX_ARR_SIZE_OBS  8
#define MAX_ARR_SIZE_EVT  16

class Observable : public ComponentInterface {
private:
  Observer* _obsList[MAX_ARR_SIZE_OBS];
  uint32_t  _obsListIdx;
  Event*    _evtList[MAX_ARR_SIZE_EVT];
  uint32_t  _evtListIdx;

public:
  explicit Observable();
  virtual ~Observable();
  void subscribe(Observer* obs);

protected:
  void pushEvent(Event* evt);
  virtual void generateEvents() = 0;

  // Override ComponentInterface
public:
  virtual bool setup();
  virtual void loop(); // 1.gen evts 2.clone _evtList 3.process cloned _evtList 

  virtual uint32_t getPeriod() const = 0;
};

#endif
