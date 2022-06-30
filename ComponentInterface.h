#ifndef _COMPONENT_INTERFACE_H_
#define _COMPONENT_INTERFACE_H_

class ComponentInterface {
public:
  virtual bool setup() = 0;
  virtual void loop() = 0;

  virtual uint32_t getPeriod() const = 0;
  virtual int32_t getValue() const = 0;
};

#endif
