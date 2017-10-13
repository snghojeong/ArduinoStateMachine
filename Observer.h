#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Data;

class Observer {
public:
  virtual void notify(Data& data) = 0;
};

#endif
