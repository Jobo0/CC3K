#ifndef CHARACHTER_H
#define CHARACHTER_H

#include "object.h"
#include <string>
#include <memory>

class Chamber;

class Charachter : public Object {
    protected:
    int ATK;
    int DEF;
    int HP;

    public:
    Charachter(char c, int atk, int def, int hp);

    virtual void move(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override;

    virtual int getATK() override;
    virtual int getDEF() override;
    virtual int getHP() override;
    virtual std::string getInfo() override;

    virtual void attack(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override; // default attack behaviour, can be overwritten
    virtual void beAttacked(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) override;
    virtual void scanAttack(std::shared_ptr<Chamber> ch, std::shared_ptr<Object> myPtr) override;
    virtual void kill(std::shared_ptr<Object> theKilled, std::shared_ptr<Object> myPtr) override;
    virtual int beKilled(std::shared_ptr<Object> o) override;

    virtual void use(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override;
    virtual void beUsed(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) override; //these should only be implemented by items for now
    virtual bool isUsed() override {return false;};

    virtual ~Charachter();
};

#endif
