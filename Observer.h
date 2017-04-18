#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
public:
  virtual void notify(Event* evt) = 0;
};

#endif
