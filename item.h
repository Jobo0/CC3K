#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <string>
#include "object.h"

class Chamber;

class Item : public Object {
    protected:
    bool used;

    public:
    Item(char c);

    void move(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override {}; 
   
    int getATK() override {return 0;} ;
    int getDEF() override {return 0;} ;
    int getHP() override {return 0;} ;


    virtual std::string getInfo() = 0;

    void attack(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override {};
    void beAttacked(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) override {}; 
    void scanAttack(std::shared_ptr<Chamber> ch, std::shared_ptr<Object> myPtr) override {};
    void kill(std::shared_ptr<Object> theKilled, std::shared_ptr<Object> myPtr) override {}; 
    int beKilled(std::shared_ptr<Object> o) override {return 0;};

    virtual void use(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) override {};
    virtual void beUsed(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) override = 0; //these should only be implemented by items for now
    bool isUsed() override;

};

#endif
