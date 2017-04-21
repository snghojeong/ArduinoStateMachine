#include <Arduino.h>

#include "ExampleStateMachine.h"

Event ExampleStateMachine::_transExEvt;

ExampleStateMachine::ExampleStateMachine() : _duringFirstState(*this), _duringSecondState(*this), _duringThirdState(*this), _duringReturnState(*this), _transitProc(*this)
{
  _firstState.registerDuring(&_duringFirstState);
  _firstState.registerEvent(&_transExEvt, &_transitProc, &_secondState);
  _secondState.registerDuring(&_duringSecondState);
  _secondState.registerEvent(&_transExEvt, &_transitProc, &_thirdState);
  _thirdState.registerDuring(&_duringThirdState);
  _thirdState.registerEvent(&_transExEvt, &_transitProc, &_returnState);
  _returnState.registerDuring(&_duringReturnState);
  _returnState.registerEvent(&_transExEvt, &_transitProc, &_firstState);

  _currState = &_firstState;
}

ExampleStateMachine::~ExampleStateMachine()
{
}

uint32_t ExampleStateMachine::getPeriod() const
{
  return 1000;
}

void ExampleStateMachine::DuringFirstState::operator()()
{
  static uint8_t cnt = 0;

  Serial.println(F("During first state."));

  if (++cnt > 10) {
    cnt = 0;
    _owner.pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::DuringSecondState::operator()()
{
  static uint8_t cnt = 0;

  Serial.println(F("During second state."));

  if (++cnt > 10) {
    cnt = 0;
    _owner.pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::DuringThirdState::operator()()
{
  static uint8_t cnt = 0;

  Serial.println(F("During third state."));

  if (++cnt > 10) {
    cnt = 0;
    _owner.pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::DuringReturnState::operator()()
{
  static uint8_t cnt = 0;

  Serial.println(F("During return state."));

  if (++cnt > 10) {
    cnt = 0;
    _owner.pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::TransitProc::operator()()
{
  Serial.println(F("Transition."));
}

