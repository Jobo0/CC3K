#ifndef GOLD_H
#define GOLD_H

#include "item.h"
#include <string>
#include <memory>

class Object;

class Gold : public Item {

    std::string goldType;

    public:
    Gold(int G);
    std::string getInfo() override;

    void beUsed(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) override;

};

#endif
