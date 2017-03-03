#include <Arduino.h>

#include "StateMachineComponent.h"
#include "AsyncConsoleComponent.h"


StateMachineComponent::StateMachineComponent(MemoryAllocator* allocator)
: _allocator(allocator), _stateList(allocator), _currState(NULL)
{
}

StateMachineComponent::~StateMachineComponent()
{
}

StateElement* StateMachineComponent::getStateElmt(const unsigned int key)
{
  ListIterator<StateElement> iter = _stateList.begin();
  while (iter != _stateList.end()) {
    StateElement& state = *iter;
    if (state == key) {
      return &state;
    }
    ++iter;
  }
  return NULL;
}

StateElement& StateMachineComponent::operator[](const unsigned int key)
{
  StateElement* state = this->getStateElmt(key);
  if (state != NULL) {
    return *state;
  }

  // Not found
  
  //return (_stateList.addNewNode()->content = key);

  //StateElement& newState = _stateList.addNewNode()->content = key;
  //newState.setMemAllocator(_allocator);
  //return newState;

  ListNode<StateElement>* newStateNode = _stateList.addNewNode();
  if (newStateNode == NULL) {
    traceln(F("[StateMachineComponent] ERROR: Memory allocation failed."));
  }

  StateElement& newState = newStateNode->content;
  newState.setMemAllocator(_allocator);
  return (newState = key);
}

bool StateMachineComponent::setup()
{
  static uint8_t t_abFsmEventQ[8];
  _eventQ.init(t_abFsmEventQ, uint8_t(sizeof(t_abFsmEventQ)/sizeof(t_abFsmEventQ[0])));
  _millisOfCurrState = millis();
  return this->initStateMachine();
}

void StateMachineComponent::loop()
{
  uint16_t bTotalEvent;
  uint8_t bI;
  uint8_t bEvent;
  bTotalEvent = _eventQ.size();
  for (bI = 0; bI < bTotalEvent; bI++)
  {
    bEvent = _eventQ.de();
    this->execEvent(bEvent);
  }
}

void StateMachineComponent::addEvent(uint8_t bEvent)
{
  _eventQ.en(bEvent);
}

void StateMachineComponent::execEvent(uint8_t bEvent)
{
  unsigned int bInstantExeEvent;
  unsigned int bCurrentEvent;
  //uint8_t bParentStateNum = (uint8_t)(-1);

  // Invalid state
  if (_currState == NULL) {
    return;
  }

  bCurrentEvent = bEvent;
  while (bCurrentEvent) {
    EventElement* evtElmt = _currState->getEvtElmt(bCurrentEvent);
    if (evtElmt == NULL) {
      break; // @Seungho TODO: Error handling.
    }

    bInstantExeEvent = (*evtElmt)(*this);
    StateElement* nextState = this->getStateElmt(evtElmt->getNextState());
    if (nextState != _currState) {
      _currState = nextState;
      _millisOfCurrState = millis();
    }

    bCurrentEvent = 0;
    if (bInstantExeEvent != 0) {
      bCurrentEvent = bInstantExeEvent;
      bInstantExeEvent = 0;
    }
  }
}

void StateMachineComponent::setState(const unsigned int key)
{
  _currState = this->getStateElmt(key);
}

unsigned long StateMachineComponent::millisOfCurrState() const
{
  return millis() - _millisOfCurrState;
}

