#include <Arduino.h>

#include "ComponentPool.h"
#include "ComponentInterface.h"
#include "StaticMemoryAllocator.h"
#include "AsyncConsoleComponent.h"
#include "ArduinoWifiComponent.h"
#include "HttpClientComponent.h"
#include "NonVolatileMemComponent.h"
#include "SensorComponent.h"


void ComponentPool::set1msLoopComponents(ComponentPool& compPool)
{
  compPool.addComponent(new AsyncConsoleComponent());
}

void ComponentPool::setMainLoopComponents(ComponentPool& compPool)
{
  compPool.addComponent(new NonVolatileMemComponent());
  //compPool.addComponent(new ArduinoWifiComponent(&(compPool._memAllocator)));
  //compPool.addComponent(new HttpClientComponent());
  //compPool.addComponent(new SensorComponent());
}

ComponentPool::ComponentPool()
{
  _compCnt = 0;
}

ComponentPool::~ComponentPool()
{
  for (int i = 0; i < _compCnt; i++) {
    delete _compArray[i];
  }
}

void ComponentPool::addComponent(ComponentInterface* comp)
{
  _compArray[_compCnt++] = comp;
}

ComponentInterface& ComponentPool::getComponent(uint16_t idx) const
{
  return *_compArray[idx];
}

uint16_t ComponentPool::length() const
{
  return _compCnt;
}
