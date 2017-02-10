#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>

#include "ArduinoWifiComponent.h"
#include "AsyncConsoleComponent.h"
#include "NonVolatileMemComponent.h"

typedef enum _E_STATE_ORDER
{
  STATE_INIT,

  STATE_CONNECT,
  STATE_WAIT,
  STATE_CONNECTED,
  STATE_DISCONNECTED,

  STATE_TOTAL_CNT
} E_STATE_ORDER;

typedef enum _E_EVENT {
  EVT_NULL = 0x00,
  EVT_INIT,
  EVT_INIT_END,
  EVT_CONNECTED, 
  EVT_FAILED, 
  EVT_CONNECT,
  EVT_WAIT,
  EVT_CHECK_CONN,
  EVT_DISCONNECTED,
} E_EVENT;


void ArduinoWifi_cmdProc(const String* cmd)
{
  int8_t indexes[5];
  int8_t para_cnt = 0;
  String strBuf;
  char charArrBuf[MAX_LEN_EEPROM_STR];

  para_cnt = argsParser(*cmd, indexes);

  if (para_cnt != 3) {
    Serial.println(F("Invalid Command"));
    return;
  }

  strBuf = cmd->substring(indexes[0], indexes[1]);
  strBuf.trim();
  strBuf.toCharArray(charArrBuf, MAX_LEN_EEPROM_STR);
  NonVolatileMemComponent::setWifiSSID(charArrBuf);

  strBuf = cmd->substring(indexes[1], indexes[2]);
  strBuf.trim();
  strBuf.toCharArray(charArrBuf, MAX_LEN_EEPROM_STR);
  NonVolatileMemComponent::setWifiPasswd(charArrBuf);

  Serial.print(F("SSID: "));
  Serial.println(NonVolatileMemComponent::getWifiSSID());
  Serial.print(F("Password: "));
  Serial.println(NonVolatileMemComponent::getWifiPasswd());
}

ArduinoWifiComponent::ArduinoWifiComponent(MemoryAllocator* allocator)
: StateMachineComponent(allocator)
{
  consoleCmd_t consoleCmd;

  // Register console command
  consoleCmd._cmd = F("wifi");
  consoleCmd._help = F("Connect Wi-fi. (Useage: wifi [SSID] [PASSWD]");
  consoleCmd._cmdProc = ArduinoWifi_cmdProc;
  if (!AsyncConsoleComponent::registerConsoleCmd(consoleCmd)) {
    return;
  }
}

ArduinoWifiComponent::~ArduinoWifiComponent()
{
}

bool ArduinoWifiComponent::initStateMachine()
{
  StateMachineComponent& stateMachine = *this;

  // Init state
  stateMachine[STATE_INIT][EVT_INIT] << &_initEntered << STATE_INIT;
  stateMachine[STATE_INIT][EVT_INIT_END] << &_initEnded << STATE_CONNECT;

  // Connect state
  stateMachine[STATE_CONNECT][EVT_CONNECTED] << &_connected << STATE_CONNECTED;
  stateMachine[STATE_CONNECT][EVT_FAILED] << &_failed << STATE_WAIT;

  // Wait state
  stateMachine[STATE_WAIT][EVT_WAIT] << &_wait << STATE_WAIT;
  stateMachine[STATE_WAIT][EVT_CONNECT] << &_connect << STATE_CONNECT;

  // Connected state
  stateMachine[STATE_CONNECTED][EVT_CHECK_CONN] << &_checkConn << STATE_CONNECTED;
  stateMachine[STATE_CONNECTED][EVT_DISCONNECTED] << &_disconnected << STATE_DISCONNECTED;

  // Disconnected state
  stateMachine[STATE_DISCONNECTED][EVT_INIT] << &_initEntered << STATE_INIT;

  stateMachine.setState(STATE_INIT);
  stateMachine.addEvent(EVT_INIT);
}

bool ArduinoWifiComponent::connectToWiFi()
{
  char ssidBuf[MAX_LEN_EEPROM_STR], passwdBuf[MAX_LEN_EEPROM_STR]; // @Seungho TODO: WiFi.begin(char*, char*) can't use const char
  int status = WL_IDLE_STATUS;

  strncpy(ssidBuf, NonVolatileMemComponent::getWifiSSID(), MAX_LEN_EEPROM_STR);
  strncpy(passwdBuf, NonVolatileMemComponent::getWifiPasswd(), MAX_LEN_EEPROM_STR);

  trace(F("[ArduinoWifiComponent] Connect to WiFi. (SSID: "));
  trace(ssidBuf);
  trace(F(", Password: "));
  trace(passwdBuf);
  traceln(F(") Please wait..."));

  status = WiFi.begin(ssidBuf, passwdBuf);
  if (status != WL_CONNECTED) {
    traceln(F("[ArduinoWifiComponent] Connect failed. Retry after 60 sec"));
    return false;
  } else {
    return true;
  }
}

uint32_t ArduinoWifiComponent::getPeriod() const
{
  return 1000;
}

unsigned int ArduinoWifiComponent::InitEntered::operator()(StateMachineComponent& stateMachine)
{
Serial.print(__FILE__);Serial.print(", ");Serial.println(__LINE__, DEC);
  if (WiFi.status() == WL_NO_SHIELD) {
    traceln(F("[ArduinoWifiComponent] WiFi shield not present."));
  } else {
    stateMachine.addEvent(EVT_INIT_END);
  }
Serial.print(__FILE__);Serial.print(", ");Serial.println(__LINE__, DEC);
  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::InitEnded::operator()(StateMachineComponent& stateMachine)
{
  if (ArduinoWifiComponent::connectToWiFi()) {
    stateMachine.addEvent(EVT_CONNECTED);
  } else {
    stateMachine.addEvent(EVT_FAILED);
  }

  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::Connected::operator()(StateMachineComponent& stateMachine)
{
  stateMachine.addEvent(EVT_CHECK_CONN);
  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::Failed::operator()(StateMachineComponent& stateMachine)
{
  stateMachine.addEvent(EVT_WAIT);
  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::Wait::operator()(StateMachineComponent& stateMachine)
{
  if (stateMachine.millisOfCurrState() > 60000) {
    stateMachine.addEvent(EVT_CONNECT);
  }
  else {
    stateMachine.addEvent(EVT_WAIT);
  }
  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::Connect::operator()(StateMachineComponent& stateMachine)
{
  if (ArduinoWifiComponent::connectToWiFi()) {
    stateMachine.addEvent(EVT_CONNECTED);
  } else {
    stateMachine.addEvent(EVT_FAILED);
  }
  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::CheckConnection::operator()(StateMachineComponent& stateMachine)
{
  if (WiFi.status() != WL_CONNECTED) {
    traceln(F("[ArduinoWifiComponent] WiFi disconnected."));
    stateMachine.addEvent(EVT_DISCONNECTED);
  } else {
    traceln(F("[ArduinoWifiComponent] WiFi connected."));
    stateMachine.addEvent(EVT_CHECK_CONN);
  }
  return EVT_NULL;
}

unsigned int ArduinoWifiComponent::Disconnected::operator()(StateMachineComponent& stateMachine)
{
  stateMachine.addEvent(EVT_INIT);
  return EVT_NULL;
}

