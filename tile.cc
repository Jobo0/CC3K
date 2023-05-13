#include "tile.h"
#include "object.h"
#include <string>
#include "objectCreator.h"
#include "player.h"

char Tile::getTile() {
    if (tileObj != nullptr) {
        return tileObj->getSymbol();
    }
    return tileSym;
}

Tile::Tile(): tileSym{' '}, tileObj{nullptr} {

}

void Tile::setTile(char c, std::shared_ptr<ObjectCreator> OC) {
    
    std::string terrain = "|- .#+";
    for (char &t : terrain) {
        if (c == t) {
            tileSym = c;
            return;
        }
    }
    // if its not one of these, then it is an object
    // which will have a floor tile underneath it
    tileSym = '.';

    tileObj = OC->createFromChar(c);
}

std::shared_ptr<Object> Tile::getObject() {
    return tileObj;
}

template<>
void Tile::setObject(std::shared_ptr<Charachter> obj) {
    tileObj = obj;
};

void Tile::removeObject() {
    tileObj = nullptr;
}

bool Tile::isCharachter() {
    if (tileObj == nullptr) {
        return false;
    } else if (tileObj->getType() == 'C') {
        return true;
    } 
    return false;
}

bool Tile::isItem() {
    if (tileObj == nullptr) {
        return false;
    } else if (tileObj->getType() == 'I') {
        return true;
    } 
    return false;
}

bool Tile::isWall() {
    if (tileSym == '|' || tileSym == '-') {
        return true;
    }
    return false;
}

bool Tile::isPassage() {
    if (tileSym == '+' || tileSym == '#') {
        return true;
    }
    return false;
}

bool Tile::isSpace() {
    if (tileSym == ' ') {
        return true;
    }
    return false;
}
