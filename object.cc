#include "object.h"


Object::Object(char c, char t): symbol{c}, type{t}, gold{0}, Action{}{
    
};

char Object::getSymbol() {
    return symbol;
}

char Object::getType() {
    return type;
}

Object* Object::getAddress() {
    return this;
}

std::string Object::getAction() {
    return Action.str();
};

void Object::addAction(std::string act) {
    Action << act;
};

void Object::resetAction() {
    Action.str("");
};


int Object::getGold() { return gold;};

void Object::setGold(int g) {gold = g;};

Object::~Object() {};

