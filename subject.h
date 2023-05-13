#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include <string>
#include "tile.h"

class Observer;


class Subject {
  std::vector<Observer*> observers;
  std::vector<Tile> state;
 protected:
  void setState(std::vector<Tile> newS);
 public:
  void attach(Observer *o);  
  void notifyObservers();
  std::vector<Tile> getState() const;
  std::vector<Tile> &getStateRef(); // break encapsulation, directly modify
};

#endif
