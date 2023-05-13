#include "gameManager.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <string>

GameManager::GameManager(): theLevel{Level{79, 25}}, theDisplay{Display{79, 25}} {
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::default_random_engine{seed};

    theLevel.attach(&theDisplay); // would be able to attach multiple displays
    //theLevel.loadLevelFile("leveltest2.txt");
    //theLevel.findChambers();
    race = 'h';

}

GameManager::GameManager(char *seed): theLevel{Level{79, 25}}, theDisplay{Display{79, 25}} {
    unsigned numSeed;
        try {
			numSeed = std::stoi( std::string{ seed } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			throw;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			throw;
		}

        rng = std::default_random_engine{numSeed};
    
    theLevel.attach(&theDisplay); // would be able to attach multiple displays
    //theLevel.loadLevelFile("leveltest2.txt");
    //theLevel.findChambers();
    race = 'h';

}

void GameManager::loadFile(std::string fileName) {
    theLevel.playerRace(race);
    theLevel.loadLevelFile(fileName, rng);
    theLevel.findChambers();

}

void GameManager::resetLevel() {
    theLevel = Level{79,25};
    theLevel.attach(&theDisplay);
}

void GameManager::chooseRace(char r) {
    race = r;
}

void GameManager::refresh() {

        theLevel.notifyObservers();

    theLevel.resetAction();
    // debug
    //std::cout << "chambers:" << std::endl;
    //theLevel.debugPrintChambers();

}

void GameManager::enemiesMove() {
    theLevel.enemiesMove(rng);
}

void GameManager::enemiesAttack() {
    theLevel.enemiesScanAttack();
}

void GameManager::actionStatus() {
    theLevel.actionSnapshot();
}

void GameManager::movePlayer(std::string dir) {
    theLevel.movePlayer(dir);
}

void GameManager::playerAttack(std::string dir) {
    theLevel.playerAttack(dir);
}

void GameManager::playerUse(std::string dir) {
    theLevel.playerUse(dir);
}

