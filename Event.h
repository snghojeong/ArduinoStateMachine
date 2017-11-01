#ifndef _SERIALIZABLE_INTERFACE_H_
#include "SerializableInterface.h"
#endif

#ifndef _DATA_H_
#include "Data.h"
#endif

#ifndef _EVENT_H_
#define _EVENT_H_

// Useage: 
// class SomeObservableClass {
//   ...
//   static Event _someEvent;
//   ...
//   someMethod() {
//     this->pushEvent(_someEvent);
//   }
//   ...
// }

class Event : public SerializableInterface {
public:
  static const Data::Type _evtDataType;

private:
  static uint32_t _nextID;
  uint32_t _id;

public:
  explicit Event() { _id = ++_nextID; }
  explicit Event(const Data& data);
  virtual ~Event() {}

  unsigned int getID() const { return _id; }
  bool operator==(const Event* evt) const { return (_id == evt->getID()); }
  bool operator==(const Event& evt) const { return (_id == evt.getID()); }

  // Override SerializableInterface
public:
  virtual const Data::Type type() const;
  virtual size_t serialize(Data& data);
  virtual void deserialize(const Data& data);
};

#endif
