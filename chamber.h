#ifndef CHAMBER_H
#define CHAMBER_H

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <random>

class Tile;

class Player;

class Charachter;

class Object;

class Chamber {
    int width;
    int height;

    std::ostringstream Action;

    std::vector<std::shared_ptr<Tile>> chamberTiles;

    // helper functions
    
    int findTarget(int location, std::string dir);
    void killIfDead(int location);

    public:
    Chamber(int width, int height);

    void spawn(std::shared_ptr<Object> o, std::default_random_engine &rng);

    int locate(std::shared_ptr<Object> o);

    void parseChamber(int horizontalStart, int verticalStart, std::vector<std::shared_ptr<Tile>> &lvl, int originalWidth);

    void move(std::shared_ptr<Object> p, std::string dir);

    void attack(std::shared_ptr<Object> c, std::string dir);

    void scanAttack(std::shared_ptr<Object> c);

    void use(std::shared_ptr<Object> c, std::string dir);

    void debugPrintChamber();

    std::string getAction();
    void actionReset();

};

#endif
