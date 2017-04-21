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

//#define MAX_ARR_SIZE_STATE 16

class StateMachine : public Observable, public Observer {
public:
  static Event _during;

protected:
  //State*    _stateList[MAX_ARR_SIZE_STATE];
  //uint32_t  _stateListIdx;
  State*    _currState;

public:
  explicit StateMachine();
  virtual ~StateMachine();

  // Override Observable
protected:
  virtual void generateEvents(); // 1.process state::during. 2.return generated events.

  // Override Observer
public:
  virtual void notify(Event* evt); // 1.seek state::evt_list. 2.change state. 3.process prev_state::exit, event::proc, next_state::enter.
};

#endif
