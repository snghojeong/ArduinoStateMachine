#ifndef _EVENT_H_
#define _EVENT_H_

class Event {
private:
  static unsigned int _id;
public:
  Event() { ++_id; }
  virtual ~Event();

  unsigned int getID() { return _id }
};

#endif
