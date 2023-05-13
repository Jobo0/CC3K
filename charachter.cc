#include "charachter.h"
#include "chamber.h"
#include <sstream>

#include <cmath>

#include <iostream>

Charachter::Charachter(char c, int atk, int def, int hp): Object(c, 'C'), ATK{atk}, DEF{def}, HP{hp} {

};

void Charachter::move(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) {
    std::ostringstream oss;
    oss << Object::getSymbol() << " moves " << dir << ".";

    Object::resetAction();
    Object::addAction(oss.str());

    ch->move(myPtr, dir);
}

int Charachter::getATK() {
    return ATK;
}

int Charachter::getDEF() {
    return DEF;
}

int Charachter::getHP() {
    return HP;
}


std::string Charachter::getInfo() {
    std::ostringstream oss;
    oss << ATK << " " << DEF << " " << HP;
    return oss.str();
};

void Charachter::attack(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) {
    Object::resetAction();
    std::ostringstream oss;
    oss << Object::getSymbol() << " deals ";
    Object::addAction(oss.str());
    ch->attack(myPtr, dir);
};

void Charachter::beAttacked(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) {
    double def = DEF;
    double atk = o->getATK();

    double damageMult = (100/(100+def));
    double dmg = std::ceil(damageMult * atk);

    
    int damage = std::ceil(dmg);
    //std::cout << "calculatedDamage" << dmg << std::endl;
    //std::cout << "attackDamage: " << o->getATK() << " defense: " << DEF << " ";
    //std::cout << "hit for " << damage << " damage" << std::endl;

    HP = HP - damage;
    
    std::ostringstream oss;
    oss << damage << " damage to " << Object::getSymbol() << " (" << HP << " HP)" << ". ";
    o->addAction(oss.str());
    
    if (HP <= 0) {
        o->kill(myPtr, o);
    }
}

void Charachter::scanAttack(std::shared_ptr<Chamber> ch, std::shared_ptr<Object> myPtr) {
    Object::resetAction();
    std::ostringstream oss;
    oss << Object::getSymbol() << " deals ";
    Object::addAction(oss.str());
    ch->scanAttack(myPtr);
};

void Charachter::kill(std::shared_ptr<Object> theKilled, std::shared_ptr<Object> myPtr) {
    std::ostringstream oss;
    oss << Object::getSymbol() << " slays ";
    Object::addAction(oss.str());
    theKilled->beKilled(myPtr);
};

int Charachter::beKilled(std::shared_ptr<Object> o)  {
    std::ostringstream oss;
    oss << Object::getSymbol() << " (" << Object::getGold() << "G). ";
    o->addAction(oss.str());
    
    return Object::getGold();
};

void Charachter::use(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr)  {
    Object::resetAction();
    std::ostringstream oss;
    oss << Object::getSymbol() << " uses ";
    Object::addAction(oss.str());

    ch->use(myPtr, dir);
};

void Charachter::beUsed(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) {

};



Charachter::~Charachter() {};


