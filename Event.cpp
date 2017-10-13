#include <Arduino.h>

#include "Event.h"
#include "Data.h"


uint32_t Event::_nextID = 0;

Event::Event(const Data& data)
{
  this->deserialize(data);
}

uint16_t Event::type()
{
  return SERIALIZABLE_TYPE_EVENT;
}

size_t Event::serialize(Data& data)
{
  data.copyFrom((uint8_t*)(&_id), sizeof(_id));
  data.setType(this->type());
  return sizeof(_id);
}

void Event::deserialize(const Data& data)
{
  data.copyTo((uint8_t*)(&_id), sizeof(_id));
}

