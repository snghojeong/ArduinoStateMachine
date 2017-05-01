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
  void (*_evtProcLambda[MAX_ARR_SIZE_STS_EVT])(StateMachine& stateMachine, uint8_t* data, size_t dataLen);
  void (*_duringLambda)(StateMachine& stateMachine, uint8_t* data, size_t dataLen);

public:
  explicit State(StateMachine& owner);
  //explicit State(Event* evtList[], EventProcedure* evtProcList[], EventProcedure* duringProc);
  // usage) static State exState({evt1, evt2, evt3}, {evtProc1, evtProc2, evtProc3}, during );
  virtual ~State();

  void registerDuring(void (*duringLambda)(StateMachine& stateMachine)) { _duringLambda = duringLambda; }
  void registerEvent(Event* evt, State* nextState, void (*evtProcLambda)(StateMachine& stateMachine));
  State* processEvent(Event* evt, uint8_t* data, size_t dataLen);
  void during(uint8_t* data, size_t dataLen) { (_duringLambda)(_owner, data, dataLen); }
};

#endif
