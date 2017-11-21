#ifdef LINUX
#include <cstddef>
#include <cstdint>
#include <cstring>
#else
#include <Arduino.h>
#endif

#include "Data.h"

uint16_t Data::Type::_nextID = 0;

