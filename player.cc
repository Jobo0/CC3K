#include "player.h"
#include "chamber.h"
#include <sstream>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <vector>

Player::Player(char c, int atk, int def, int hp): Charachter(c, atk, def, hp) {
    rng = std::default_random_engine{std::chrono::system_clock::now().time_since_epoch().count()};
}

void Player::attack(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) {
    Object::resetAction();
    std::ostringstream oss;
    oss << "PC" << " deals ";
    Object::addAction(oss.str());
    ch->attack(myPtr, dir);
};

void Player::kill(std::shared_ptr<Object> theKilled, std::shared_ptr<Object> myPtr) {
    std::ostringstream oss;
    oss << "PC" << " slays ";
    Object::addAction(oss.str());

    int g = theKilled->beKilled(myPtr);
    g = g + Object::getGold();
    Object::setGold(g);
};

int Player::beKilled(std::shared_ptr<Object> o)  {
    std::ostringstream oss;
    oss << Object::getSymbol() << " (" << Object::getGold() << "G). Player is dead.";
    o->addAction(oss.str());
    return Object::getGold();
};

void Player::beAttacked(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) {
    std::vector<int> v {1, 2};

    double def = DEF;
    double atk = o->getATK();

    double damageMult = (100/(100+def));
    double dmg = std::ceil(damageMult * atk);

    int damage = std::ceil(dmg);


    //std::cout << "calculatedDamage" << dmg << std::endl;
    //std::cout << "attackDamage: " << o->getATK() << " defense: " << DEF << " ";
    //std::cout << "hit for " << damage << " damage" << std::endl;

    std::ostringstream oss;

    std::shuffle(v.begin(), v.end(), rng );
    if (v[0] == 1) {
        HP = HP - damage;
        oss << damage << " damage to " << "PC. ";
        o->addAction(oss.str());
    } else {
        oss << damage << "(miss) damage to " << "PC. ";
        o->addAction(oss.str());
    }
    
    if (HP <= 0) {
        o->kill(myPtr, o);
    }
}

std::string Player::getInfo() {
    std::ostringstream oss;
    oss << Charachter::getInfo() << " " << Object::getGold();
    return oss.str();
}

Player::~Player() {};

