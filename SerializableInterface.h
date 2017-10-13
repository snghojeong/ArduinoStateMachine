#ifndef _SERIALIZABLE_INTERFACE_H_
#define _SERIALIZABLE_INTERFACE_H_

#define SERIALIZABLE_TYPE_EVENT 1

class Data;

class SerializableInterface {
public:
  virtual uint16_t type() = 0;
  virtual size_t serialize(Data& data) = 0;
  virtual void deserialize(const Data& data) = 0;
};

#endif
