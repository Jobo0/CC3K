#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "display.h"
#include "level.h"


#include <random>
#include <string>


class GameManager {

    char race;
    Level theLevel;
    Display theDisplay;

    std::default_random_engine rng;

    public:
    GameManager();
    GameManager(char *seed);

    void chooseRace(char r);
    void loadFile(std::string fileName);
    void resetLevel();

    void refresh(); // refreshes all displays (if had multiple displays)

    void enemiesMove();
    void enemiesAttack();

    void actionStatus();

    void movePlayer(std::string dir);
    void playerAttack(std::string dir);
    void playerUse(std::string dir);

    
};

#endif
