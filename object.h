#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>
#include <sstream>

class Chamber;

class Object {
    std::ostringstream Action;

    int gold;
    char symbol;
    char type;
    public:
    Object(char c, char t);
    char getSymbol();
    char getType(); // C for charachter, I for item, S for stair
    Object* getAddress();

    virtual void move(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) = 0; // make these pure virual, later


    virtual int getATK() = 0;
    virtual int getDEF() = 0;
    virtual int getHP() = 0;
    virtual int getGold();
    virtual void setGold(int g);
    virtual std::string getInfo() = 0;

    std::string getAction();
    void addAction(std::string act);
    void resetAction();

    virtual void attack(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) = 0;
    virtual void beAttacked(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) = 0; //these should only be implemented by charachters, deleted by items
    virtual void scanAttack(std::shared_ptr<Chamber> ch, std::shared_ptr<Object> myPtr) = 0;
    virtual void kill(std::shared_ptr<Object> theKilled, std::shared_ptr<Object> myPtr) = 0; // this is dumb i think
    virtual int beKilled(std::shared_ptr<Object> o) = 0;

    virtual void use(std::shared_ptr<Chamber> ch, std::string dir, std::shared_ptr<Object> myPtr) = 0;
    virtual void beUsed(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) = 0; //these should only be implemented by items for now
    virtual bool isUsed() = 0;

    virtual ~Object() = 0; // including this
};

#endif
