#include "gold.h"

#include <sstream>

Gold::Gold(int G): Item{'G'} {
    Object::setGold(G);
    if (G == 1) {
        goldType= "normal";
    } else if (G == 2) {
        goldType = "small hoard";
    } else if (G <= 4) {
        goldType = "merchant hoard";
    } else {
        goldType = "dragon hoard";
    }
}

std::string Gold::getInfo() {
    std::ostringstream oss;
    oss << Object::getGold() << " " << goldType;
    return oss.str();
}

void Gold::beUsed(std::shared_ptr<Object> o, std::shared_ptr<Object> myPtr) {
    std::ostringstream oss;
    oss << "Gold(" << Object::getGold() << "). ";
    o->addAction(oss.str());

    int G = o->getGold();
    G = G + Object::getGold();
    o->setGold(G);
    used = true;
}



