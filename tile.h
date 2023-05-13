#ifndef TILE_H
#define TILE_H

#include <memory>

class Object;

class ObjectCreator;

class Tile {
    char tileSym;
    std::shared_ptr<Object> tileObj;
    public:
    Tile();
    char getTile();
    void setTile(char c, std::shared_ptr<ObjectCreator> OC);
    std::shared_ptr<Object> getObject();

    template <typename T>
    void setObject(std::shared_ptr<T> obj);

    void removeObject();
    bool isCharachter();
    bool isItem();
    bool isWall();
    bool isPassage();
    bool isSpace();
};

template <typename T>
void Tile::setObject(std::shared_ptr<T> obj) {
    tileObj = obj;
};

#endif
