#include "subject.h"
#include "observer.h"

void Subject::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
};

void Subject::setState(std::vector<Tile> newS) { state = newS; };

std::vector<Tile> Subject::getState() const { return state; };

std::vector<Tile> & Subject::getStateRef() { return state; };
