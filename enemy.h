#ifndef ENEMY_H
#define ENEMY_H

#include "charachter.h"

class Enemy : public Charachter {

    public:
    Enemy(char c, int atk, int def, int hp);

    virtual ~Enemy();
};

#endif
