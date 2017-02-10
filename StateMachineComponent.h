#ifndef _COMPONENT_INTERFACE_H_
#include "ComponentInterface.h"
#endif

#ifndef _LIST_H_
#include "List.h"
#endif

#ifndef _STATE_ELEMENT_H_
#include "StateElement.h"
#endif

#ifndef __QUE_H__
#include "util/CircularQueue.h"
#endif

#ifndef _STATE_MACHINE_COMPONENT_H_
#define _STATE_MACHINE_COMPONENT_H_

class StateMachineComponent : public ComponentInterface {
private:
  MemoryAllocator* _allocator;
  List<StateElement> _stateList;
  S_QUE<uint8_t> _eventQ;

  StateElement* _currState;
  unsigned long _millisOfCurrState;

public:
  explicit StateMachineComponent(MemoryAllocator* allocator);
  virtual ~StateMachineComponent();

  //template <typename TStateKey>
  //StateElement& operator[](const TStateKey& key);
  StateElement& operator[](const unsigned int key);

  void addEvent(uint8_t bEvent);
  void setState(const unsigned int key);
  unsigned long millisOfCurrState() const;

private:
  void execEvent(uint8_t bEvent);
  StateElement* getStateElmt(const unsigned int key);

protected:
  virtual bool initStateMachine() = 0;

  // Override ComponentInterface
public:
  virtual bool setup();
  virtual void loop();

  virtual uint32_t getPeriod() const = 0;
};

#endif
