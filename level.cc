#include "level.h"
#include "observer.h"
#include <iostream>
#include "chamber.h"
#include "player.h"
#include "object.h"
#include <algorithm>
#include "objectCreator.h"

Level::Level(int width, int height): width{width}, height{height}, PC{nullptr}, Action{""}, PlAction{""} {
    state = std::vector<std::shared_ptr<Tile>>(width*height);
    for (auto &i : state) {
      i = std::make_shared<Tile>();
    }
    chambers = std::vector<std::shared_ptr<Chamber>>(5);
    lvlChamber = nullptr;
    /*for (auto &c : chambers) {
      c = std::make_shared<Chamber>();
    }*/
    
}

bool Level::inBox(int horizontalStart, int verticalStart, int width, int height, int originalWidth, int location) {
  for (int i = verticalStart; i < verticalStart + height; i++) {
    if (location >= (i * originalWidth) + horizontalStart && location < (i*originalWidth) + horizontalStart + width) {
      return true;
    }
  }
  return false;
};

int Level::whichChamber(int location) { // manually define where the chambers are
  if (inBox(2, 2, 28, 6, width, location)) {
    return 0;
  }
  if (inBox(3, 14, 23, 9, width, location)) {
    return 3;
  }
  if (inBox(37, 9, 14, 5, width, location)) {
    return 2;
  }
  if (inBox(36, 15, 41, 8, width, location)) {
    return 4;
  }
  // avoids the overlap by checking for chamber 2 first 
  if (inBox(38, 2, 39, 12, width, location)) {
    return 1;
  }
  return 0;
}

void Level::loadLevelFile(std::string fileName, std::default_random_engine &rng) {
    std::ifstream ifs(fileName);
    for (int i = 0; i < height; i++) {
        int displacement = i * width;
        std::string s;
        std::getline(ifs, s);
        for (int j = 0; j < width; j++) {
            state[j + displacement]->setTile(s[j], objCreator);
            if (s[j] == '@') {
              PC = state[j+displacement]->getObject();
              plLocation = j + displacement;
              playerChamber = whichChamber(plLocation);
            }
            if (s[j] == 'V' || s[j] == 'W' || s[j] == 'T' || s[j] == 'N' || s[j] == 'M' || s[j] == 'D' || s[j] == 'X') {
              enemies[state[j+displacement]->getObject()] = whichChamber(j+displacement);
            }
        }
    }
    /*if (PC == nullptr) {
      PC = objCreator->createFromChar('@');
      std::cout << "PC CREATED" << PC->getSymbol() << std::endl;
      randomSpawn(PC, rng);
    }*/
    Action << "Player spawned. ";
}

void Level::randomSpawn(std::shared_ptr<Object> o, std::default_random_engine &rng) {
    std::vector<int> v {0, 1, 2, 3, 4};
    std::shuffle(v.begin(), v.end(), rng);
    chambers[v[0]]->spawn(o, rng);
}

void Level::playerRace(char race) {
    objCreator = std::make_shared<ObjectCreator>(race);
    plRace = race;
}

void Level::movePlayer(std::string dir) {
    
    //PC->move(chambers[playerChamber], dir, PC); 
    PC->move(lvlChamber, dir, PC); 
    plLocation = lvlChamber->locate(PC);
    if (state[plLocation]->isPassage()) {
      playerChamber = whichChamber(plLocation);
    }
    
    Action << PC->getAction();

    // mistake: should have allowed players/objects to just know their own coordinates


}

void Level::playerAttack(std::string dir) {

    PC->attack(chambers[playerChamber], dir, PC);
      //Action << chambers[playerChamber]->getAction();


}

void Level::playerUse(std::string dir) {

    PC->use(chambers[playerChamber], dir, PC);
    Action << chambers[playerChamber]->getAction();


}

std::string Level::getPlayerInfo() { // returns "HP ATK DEF GOLD"
    return PC->getInfo();
}

char Level::getPlayerRace() {
  return plRace;
}

void Level::enemiesScanAttack() {
    for (auto const &E : enemies) {
      if (E.second == playerChamber) {
        E.first->scanAttack(chambers[E.second], E.first);
        
      }
    }
    Action << chambers[playerChamber]->getAction();
    //std::cout << PC->getInfo() << std::endl;
    //std::cout << "PC INFO GOT" << std::endl;
};

void Level::enemiesMove(std::default_random_engine &rng) {
    std::vector<std::string> dirVec = { "no", "so", "ea", "we", "ne", "nw", "se", "sw" };
    
    for (auto const &E : enemies) {
        std::shuffle( dirVec.begin(), dirVec.end(), rng );
        E.first->move(chambers[E.second], dirVec[0] , E.first);
        
    }
    resetAction();
}


void Level::findChambers() { // manual level & chamber setup
    chambers[0] = std::make_shared<Chamber>(28, 6);
    chambers[0]->parseChamber(2, 2, state, width);

    chambers[1] = std::make_shared<Chamber>(39, 12);
    chambers[1]->parseChamber(38, 2, state, width);

    chambers[2] = std::make_shared<Chamber>(14, 5);
    chambers[2]->parseChamber(37, 9, state, width);

    chambers[3] = std::make_shared<Chamber>(23, 9);
    chambers[3]->parseChamber(3, 14, state, width);

    chambers[4] = std::make_shared<Chamber>(41, 8);
    chambers[4]->parseChamber(36, 15, state, width);

    lvlChamber = std::make_shared<Chamber>(width, height);
    lvlChamber->parseChamber(0, 0, state, width);

}

void Level::debugPrintChambers() {
    for (auto &c : chambers) {
      c->debugPrintChamber();
      std::cout << std::endl;
    }
}

std::string Level::getAction() {
    return PlAction.str();
}

void Level::resetAction() {
    Action = std::ostringstream{}; 
    for (auto &c : chambers) {
      c->actionReset();
    }
};

void Level::actionSnapshot() {
    PlAction = std::ostringstream{Action.str()};
}

void Level::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

void Level::attach(Observer *o) {
  observers.emplace_back(o);
};

std::vector<std::shared_ptr<Tile>> Level::getState() const { return state; };

std::vector<std::shared_ptr<Tile>> & Level::getStateRef() { return state; };
