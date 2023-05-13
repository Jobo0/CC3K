#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include "tile.h"
#include <map>
#include <random>
#include <sstream>

class Observer;

class Charachter;

class Chamber;

class Object;

class ObjectCreator;

class Level {
    int width;
    int height;
    std::vector<Observer*> observers;
    std::vector<std::shared_ptr<Tile>> state;
    std::vector<std::shared_ptr<Chamber>> chambers;

    std::shared_ptr<Chamber> lvlChamber;


    char plRace;
    std::shared_ptr<ObjectCreator> objCreator; //this matters for what race will be created

    // could use std::pair but dont want to include utility
    int playerChamber;
    std::shared_ptr<Object> PC;
    int plLocation;

    std::ostringstream PlAction;
    std::ostringstream Action;

    std::map<std::shared_ptr<Object>, int> enemies; // enemies, and chamber they are in
    //std::vector<std::shared_ptr<Object>> enemies;

    // helpers
    int whichChamber(int location);
    bool inBox(int horizontalStart, int verticalStart, int width, int height, int originalWidth, int location);

    public:
    Level(int width, int height);
    void loadLevelFile(std::string fileName, std::default_random_engine &rng);

    void randomSpawn(std::shared_ptr<Object> o, std::default_random_engine &rng);

    void playerRace(char race);

    // potentially move to chamber class
    // void move(Charachter &c);

    void movePlayer(std::string dir);
    void playerAttack(std::string dir);
    void playerUse(std::string dir);

    std::string getPlayerInfo();
    char getPlayerRace();

    void enemiesScanAttack();
    void enemiesMove(std::default_random_engine &rng);

    void findChambers();
    void debugPrintChambers();

    std::string getAction();
    void resetAction();
    void actionSnapshot();

    void attach(Observer *o);  
    void notifyObservers();
    std::vector<std::shared_ptr<Tile>> getState() const;
    std::vector<std::shared_ptr<Tile>> &getStateRef(); // break encapsulation, directly modify
};

#endif
