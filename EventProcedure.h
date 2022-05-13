#ifndef _EVENT_PROCEDURE_H_
#define _EVENT_PROCEDURE_H_

class StateMachine;

class EventProcedure {
protected:
  StateMachine& _owner;
public:
  explicit EventProcedure(StateMachine& stateMachine) : _owner(stateMachine) {}
  virtual void operator() = 0;
};

#endif
