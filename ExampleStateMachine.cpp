#include <Arduino.h>

#include "ExampleStateMachine.h"

Event ExampleStateMachine::_transExEvt;

ExampleStateMachine::ExampleStateMachine()
  : StateMachine(&_firstState), _firstState(*this), _secondState(*this), _thirdState(*this), _returnState(*this)
{
  _firstState.registerDuring([](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.duringFirstState();
      });
  _firstState.registerEvent(&_transExEvt, &_secondState, [](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.transit();
      });
  _secondState.registerDuring([](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.duringSecondState();
      });
  _secondState.registerEvent(&_transExEvt, &_thirdState, [](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.transit();
      });
  _thirdState.registerDuring([](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.duringThirdState();
      });
  _thirdState.registerEvent(&_transExEvt, &_returnState, [](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.transit();
      });
  _returnState.registerDuring([](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.duringReturnState();
      });
  _returnState.registerEvent(&_transExEvt, &_firstState, [](StateMachine& owner) {
      ExampleStateMachine& thisRef = (ExampleStateMachine&)(owner); // TODO: We should handing exception.
      thisRef.transit();
      });

  _currState = &_firstState;
}

ExampleStateMachine::~ExampleStateMachine()
{
}

uint32_t ExampleStateMachine::getPeriod() const
{
  return 1000;
}

void ExampleStateMachine::duringFirstState()
{
  static uint8_t cnt = 0;

  Serial.println(F("During first state."));

  if (++cnt > 10) {
    cnt = 0;
    this->pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::duringSecondState()
{
  static uint8_t cnt = 0;

  Serial.println(F("During second state."));

  if (++cnt > 10) {
    cnt = 0;
    this->pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::duringThirdState()
{
  static uint8_t cnt = 0;

  Serial.println(F("During third state."));

  if (++cnt > 10) {
    cnt = 0;
    this->pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::duringReturnState()
{
  static uint8_t cnt = 0;

  Serial.println(F("During return state."));

  if (++cnt > 10) {
    cnt = 0;
    this->pushEvent(&_transExEvt);
  }
}

void ExampleStateMachine::transit()
{
  Serial.println(F("Transition."));
}

