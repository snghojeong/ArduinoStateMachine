#ifndef _EVENT_PROCEDURE_H_
#include "EventProcedure.h"
#endif

#ifndef _STATE_H_
#define _STATE_H_

#define MAX_ARR_SIZE_STS_EVT 16

class Event;

class State {
private:
  Event*    _evtList[MAX_ARR_SIZE_STS_EVT];
  EventProcedure* _evtProcList[MAX_ARR_SIZE_STS_EVT];
  State* _nextState[MAX_ARR_SIZE_STS_EVT];
  uint32_t  _evtListIdx;
  EventProcedure* _duringProc;

public:
  explicit State();
  //explicit State(Event* evtList[], EventProcedure* evtProcList[], EventProcedure* duringProc);
  // usage) static State exState({evt1, evt2, evt3}, {evtProc1, evtProc2, evtProc3}, during );
  virtual ~State();

  void registerDuring(EventProcedure* duringProc) { _duringProc = duringProc; }
  void registerEvent(Event* evt, EventProcedure* evtProc, State* nextState);
  State* processEvent(Event* evt);
  void during() { (*_duringProc)(); }
};

#endif
