#ifndef OBJECT_CREATOR_H
#define OBJECT_CREATOR_H

#include <memory>

class Object;

class ObjectCreator {
    char playerRace;
    public:
    ObjectCreator(char pRace);
    std::shared_ptr<Object> createFromChar(char c);
};

#endif
