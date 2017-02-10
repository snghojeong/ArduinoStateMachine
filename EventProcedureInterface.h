#ifndef _EVENT_PROCEDURE_INTERFACE_H_
#define _EVENT_PROCEDURE_INTERFACE_H_

class StateMachineComponent;

class EventProcedureInterface {
public:
  virtual unsigned int operator()(StateMachineComponent& stateMachine) = 0;
};

#endif
