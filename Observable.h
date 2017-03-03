#ifndef _COMPONENT_INTERFACE_H_
#include <ComponentInterface.h>
#endif

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

class Observable : public ComponentInterface {
private:
  List<Observer&> _obsList;
  List<Event&> _evtList;

public:
  void subscribe(Observer& obs);

protect:
  void pushEvent(Event& evt);
  virtual List<Event&>& generateEvents() = 0;

  // Override ComponentInterface
public:
  virtual bool setup();
  virtual void loop(); // 1.gen evts 2.clone _evtList 3.process cloned _evtList 

  virtual uint32_t getPeriod() const = 0;
};

#endif
