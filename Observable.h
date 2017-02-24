#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

class Observable {
public:
  void subscribe(Observer& obs);

protect:
  void pushEvent(Event evt);
};

#endif
