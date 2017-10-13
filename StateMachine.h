#ifndef _OBSERVABLE_H_
#include "Observable.h"
#endif

#ifndef _OBSERVER_H_
#include "Observer.h"
#endif

#ifndef _STATE_H_
#include "State.h"
#endif

#ifndef _EVENT_H_
#include "Event.h"
#endif

#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

class StateMachine : public Observable, public Observer {
protected:
  State*    _currState;

public:
  explicit StateMachine(State* initState);
  virtual ~StateMachine();

  void pushEvent(Event* evt);

  // Override Observable
protected:
  virtual void generateData();

  // Override Observer
public:
  virtual void notify(Data& data);
};

#endif
