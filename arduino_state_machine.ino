#include <Arduino.h>
#include <Wire.h>

#include <TimerOne.h>

#include "ComponentInterface.h"
#include "ComponentPool.h"


void timer1msLoop();


static ComponentPool g_1msLoopCompPool;
static ComponentPool g_mainLoopCompPool;
static unsigned long g_1msCompLastExecTime[8] = { 0 }; // @Seunogho TODO: Size is hard coded.
static unsigned long g_mainCompLastExecTime[8] = { 0 }; // @Seunogho TODO: Size is hard coded.


void setup()
{
  Serial.begin(115200);
  Serial.println(F("boot up"));
  Wire.begin();

  ComponentPool::set1msLoopComponents(g_1msLoopCompPool);
  ComponentPool::setMainLoopComponents(g_mainLoopCompPool);

  Serial.println(F("Init 1ms components."));
  for (int i = 0; i < g_1msLoopCompPool.length(); i++) {
    ComponentInterface& comp = g_1msLoopCompPool.getComponent(i);
    if (!comp.setup()) {
      // @Seungho TODO: Error handling..
      Serial.println(F("Init failed. System halt."));
      while(true);
    }
  }

  Serial.println(F("Init main components."));
  for (int i = 0; i < g_mainLoopCompPool.length(); i++) {
    ComponentInterface& comp = g_mainLoopCompPool.getComponent(i);
    if (!comp.setup()) {
      // @Seungho TODO: Error handling..
      Serial.println(F("Init failed. System halt."));
      while(true);
    }
  }

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timer1msLoop);
}

void loop()
{
  for (int i = 0; i < g_mainLoopCompPool.length(); i++) {
    ComponentInterface& comp = g_mainLoopCompPool.getComponent(i);
    if ((millis() - g_mainCompLastExecTime[i]) > comp.getPeriod()) {
      comp.loop();
      g_mainCompLastExecTime[i] = millis();
    }
  }
}

void timer1msLoop()
{
  for (int i = 0; i < g_1msLoopCompPool.length(); i++) {
    ComponentInterface& comp = g_1msLoopCompPool.getComponent(i);
    if ((millis() - g_1msCompLastExecTime[i]) > comp.getPeriod()) {
      comp.loop();
      g_1msCompLastExecTime[i] = millis();
    }
  }
}
