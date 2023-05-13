#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Level;

class Observer {
 public:
  virtual void notify(Level &whoFrom) = 0; // pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif
