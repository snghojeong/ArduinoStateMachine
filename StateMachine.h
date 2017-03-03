#ifndef _COMPONENT_INTERFACE_H_
#include "ComponentInterface.h"
#endif

#ifndef _LIST_H_
#include "List.h"
#endif

#ifndef _STATE_ELEMENT_H_
#include "StateElement.h"
#endif

#ifndef __QUE_H__
#include "util/CircularQueue.h"
#endif

#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

class StateMachine : public Observable, public Observer {
private:
  List<StateElement> _stateList;
  StateElement* _currState;

public:
  explicit StateMachine();
  virtual ~StateMachine();

  // Override Observable
protect:
  virtual List<Event&>& generateEvents(); // 1.process state::during. 2.return generated events.

  // Override Observer
public:
  virtual void notify(Event evt); // 1.seek state::evt_list. 2.change state. 3.process prev_state::exit, event::proc, next_state::enter.
};

#endif
