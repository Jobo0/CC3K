#include "enemy.h"

Enemy::Enemy(char c, int atk, int def, int hp): Charachter(c, atk, def, hp) {
    Object::setGold(1);
};

Enemy::~Enemy() {
    
};


