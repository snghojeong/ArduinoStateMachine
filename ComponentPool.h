#ifndef _COMPONENT_POOL_H_
#define _COMPONENT_POOL_H_

#define MAX_NUM_OF_COMP 16

class ComponentInterface;

class ComponentPool {
private:
  ComponentInterface* _compArray[MAX_NUM_OF_COMP];
  uint16_t _compCnt;

public:
  static void set1msLoopComponents(ComponentPool& compPool);
  static void setMainLoopComponents(ComponentPool& compPool);

public:
  ComponentPool();
  virtual ~ComponentPool();

  uint16_t length() const;
  void addComponent(ComponentInterface* comp);
  ComponentInterface& getComponent(uint16_t idx) const;
};

#endif
