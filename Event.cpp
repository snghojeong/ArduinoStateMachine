#ifdef LINUX
#include <cstddef>
#include <cstdint>
#include <cstring>
#else
#include <Arduino.h>
#endif

#include "Event.h"


const Data::Type _evtDataType;
uint32_t Event::_nextID = 0;

Event::Event(const Data& data)
{
  this->deserialize(data);
}

const Data::Type Event::type() const
{
  return _evtDataType;
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

