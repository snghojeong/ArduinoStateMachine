#ifndef _STATE_H_
#define _STATE_H_

#define MAX_ARR_SIZE_STS_EVT 16

class Event;
class StateMachine;

class State {
private:
  StateMachine& _owner;
  Event*        _evtList[MAX_ARR_SIZE_STS_EVT];
  State*        _nextState[MAX_ARR_SIZE_STS_EVT];
  uint32_t      _evtListIdx;
  void (*_evtProcLambda[MAX_ARR_SIZE_STS_EVT])(StateMachine& stateMachine);
  void (*_duringLambda)(StateMachine& stateMachine);

public:
  explicit State(StateMachine& owner);
  virtual ~State();

  void registerDuring(void (*duringLambda)(StateMachine& stateMachine)) { _duringLambda = duringLambda; }
  void registerEvent(Event* evt, State* nextState, void (*evtProcLambda)(StateMachine& stateMachine));
  State* processEvent(Event& evt);
  void during() { (_duringLambda)(_owner); }
};

#endif
