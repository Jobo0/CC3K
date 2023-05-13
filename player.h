#ifndef PLAYER_H
#define PLAYER_H

#include "charachter.h"
#include <string>
#include <memory>
#include <random>

class Chamber;

class Player : public Charachter {
    std::default_random_engine rng;

    public:
    Player(char c, int atk, int def, int hp);
    std::string getInfo() override;
    
    virtual void attack(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override;

    virtual void kill(std::shared_ptr<Object> theKilled, std::shared_ptr<Object> myPtr) override;
    
    virtual void beAttacked(std::shared_ptr<Object>, std::shared_ptr<Object> myPtr) override;

    virtual ~Player();
};

#endif
