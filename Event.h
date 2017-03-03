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
  static unsigned int _id;
public:
  Event() { ++_id; }
  virtual ~Event();

  unsigned int getID() const { return _id }
};

#endif
