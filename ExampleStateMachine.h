#ifndef _STATE_MACHINE_H_
#include "StateMachine.h"
#endif

#ifndef _EVENT_PROCEDURE_H_
#include "EventProcedure.h"
#endif

#ifndef _EXAMPLE_STATE_MACHINE_H_
#define _EXAMPLE_STATE_MACHINE_H_

class ExampleStateMachine : public StateMachine {
private:
  State _firstState;
  State _secondState;
  State _thirdState;
  State _returnState;

public:
  static Event _transExEvt;

public:
  explicit ExampleStateMachine();
  virtual ~ExampleStateMachine();

  // Override ComponentInterface
public:
  virtual uint32_t getPeriod() const;

  // Event procedure define
private:
  class DuringFirstState : public EventProcedure {
  public:
    explicit DuringFirstState(StateMachine& stateMachine) : EventProcedure(stateMachine) {}
    virtual void operator()();
  };
  DuringFirstState _duringFirstState;

  class DuringSecondState : public EventProcedure {
  public:
    explicit DuringSecondState(StateMachine& stateMachine) : EventProcedure(stateMachine) {}
    virtual void operator()();
  };
  DuringSecondState _duringSecondState;

  class DuringThirdState : public EventProcedure {
  public:
    explicit DuringThirdState(StateMachine& stateMachine) : EventProcedure(stateMachine) {}
    virtual void operator()();
  };
  DuringThirdState _duringThirdState;

  class DuringReturnState : public EventProcedure {
  public:
    explicit DuringReturnState(StateMachine& stateMachine) : EventProcedure(stateMachine) {}
    virtual void operator()();
  };
  DuringReturnState _duringReturnState;

  class TransitProc : public EventProcedure {
  public:
    explicit TransitProc(StateMachine& stateMachine) : EventProcedure(stateMachine) {}
    virtual void operator()();
  };
  TransitProc _transitProc;
};

#endif
