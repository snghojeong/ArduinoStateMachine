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
public:
  static Event _during;

protected:
  State*    _currState;

public:
  explicit StateMachine(State* initState);
  virtual ~StateMachine();

  // Override Observable
protected:
  virtual void generateEvents();

  // Override Observer
public:
  virtual void notify(Event* evt);
};

#endif
