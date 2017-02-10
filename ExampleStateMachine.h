#ifndef _STATE_MACHINE_COMPONENT_H_
#include "StateMachineComponent.h"
#endif

#ifndef _EVENT_PROCEDURE_INTERFACE_H_
#include "EventProcedureInterface.h"
#endif

#ifndef _ARDUINO_WIFI_COMPONENT_H_
#define _ARDUINO_WIFI_COMPONENT_H_

class ArduinoWifiComponent : public StateMachineComponent {
public:
  explicit ArduinoWifiComponent();
  explicit ArduinoWifiComponent(MemoryAllocator* allocator);
  virtual ~ArduinoWifiComponent();

  static bool connectToWiFi(); // @Seungho TODO: Find another pattern. (delete static, private encapsulation)

protected:
  virtual bool initStateMachine();

  // Override ComponentInterface
public:
  virtual uint32_t getPeriod() const;

  // Event procedure define
private:
  class InitEntered : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  InitEntered _initEntered;

  class InitEnded : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  InitEnded _initEnded;

  class Connected : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  Connected _connected;

  class Failed : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  Failed _failed;

  class Wait : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  Wait _wait;

  class Connect : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  Connect _connect;

  class CheckConnection : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  CheckConnection _checkConn;

  class Disconnected : public EventProcedureInterface {
  public:
    virtual unsigned int operator()(StateMachineComponent& stateMachine);
  };
  Disconnected _disconnected;
};

#endif
