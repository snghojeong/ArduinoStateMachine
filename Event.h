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

class Event {
private:
  static uint32_t _nextID;
  uint32_t _id;
public:
  explicit Event() { _id = ++_nextID; }
  virtual ~Event() {}

  unsigned int getID() const { return _id; }
  bool operator==(const Event* evt) const { return (_id == evt->getID()); }
  bool operator==(const Event& evt) const { return (_id == evt.getID()); }
};

#endif
