#ifndef _DATA_H_
#include "Data.h"
#endif

#ifndef _SERIALIZABLE_INTERFACE_H_
#define _SERIALIZABLE_INTERFACE_H_

class SerializableInterface {
public:
  virtual const Data::Type type() const = 0;
  virtual size_t serialize(Data& data) = 0;
  virtual void deserialize(const Data& data) = 0;
};

#endif
