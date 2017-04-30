#ifndef _STATE_MACHINE_H_
#include "StateMachine.h"
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
  void duringFirstState();
  void duringSecondState();
  void duringThirdState();
  void duringReturnState();
  void transit();
};

#endif
