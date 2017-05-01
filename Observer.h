#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
public:
  virtual void notify(Event* evt, uint8_t* data, size_t dataLen) = 0;
};

#endif
