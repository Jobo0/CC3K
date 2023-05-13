#include "chamber.h"
#include <iostream>
#include "tile.h"
#include "player.h"
#include "charachter.h"
#include "object.h"
#include <sstream>
#include <string>
#include <algorithm>



Chamber::Chamber(int width, int height): width{width}, height{height}, Action{""} {
    chamberTiles = std::vector<std::shared_ptr<Tile>>(width * height);
    for (auto &i : chamberTiles) {
        i = std::make_shared<Tile>();
    }
}

void Chamber::spawn(std::shared_ptr<Object> o, std::default_random_engine &rng) {
    std::uniform_int_distribution<int> distribution(1, width * height - 1);
    for (int i = 0; i < 10; i++) {
        int random_number = distribution(rng);
        if (chamberTiles[random_number]->getTile() == '.') {
            chamberTiles[random_number]->setObject(o);
            break;
        }
    }

}

void Chamber::parseChamber(int horizontalStart, int verticalStart, std::vector<std::shared_ptr<Tile>> &lvl, int originalWidth) {
    int k = 0;
    for (int i = verticalStart; i < verticalStart + height; i++) {
        int displacement = i * originalWidth;
        for (int j = horizontalStart; j < horizontalStart + width; j++) {
            chamberTiles[k] = lvl[j + displacement];
            k++;
        }
    }
}

int Chamber::locate(std::shared_ptr<Object> o) {
    int location = -1;
    for (int i = 0; i < height; i++) {
        int displacement = i * width;
        for (int j = 0; j < width; j++) {
            if (o == chamberTiles[j + displacement]->getObject()) {
                location = j+displacement;
                break;
            }
        }
    }
    return location;
}

int Chamber::findTarget(int location, std::string dir) {
    int target;
    if (dir == "no") {
        target = location - width;
    } else if (dir == "so") {
        target = location + width;
    } else if (dir == "ea") {
        target = location + 1;
    } else if (dir == "we") {
        target = location - 1;
    } else if (dir == "ne") {
        target = location - width + 1;
    } else if (dir == "nw") {
        target = location - width - 1;
    } else if (dir == "se") {
        target = location + width + 1;
    } else if (dir == "sw") {
        target = location + width - 1;
    }
    if (target < 0 || target >= width * height) {
        return -1;
    }
    if (chamberTiles[target]->isWall() || chamberTiles[target]->isSpace()) {
        return -1;
    }
    return target;
}

void Chamber::killIfDead(int location) {

    if (chamberTiles[location]->isCharachter()) {
        if (chamberTiles[location]->getObject()->getHP() <= 0) {
            chamberTiles[location]->removeObject();
        }
    } else if (chamberTiles[location]->isItem()) {
        if (chamberTiles[location]->getObject()->isUsed()) {
            chamberTiles[location]->removeObject();
        }
    }
}

void Chamber::move(std::shared_ptr<Object> p, std::string dir) {
    int location = locate(p);
    if (location == -1) return;

    int target = findTarget(location, dir);
    if (target == -1) return;

    if (!chamberTiles[target]->isCharachter() && !chamberTiles[target]->isItem()) {
            Action << p->getAction();
            chamberTiles[target]->setObject(p);
            chamberTiles[location]->removeObject();
    }
}

void Chamber::attack(std::shared_ptr<Object> c, std::string dir) {
    int location = locate(c);
    if (location == -1) return;

    int target = findTarget(location, dir);
    if (target == -1) return;



    if (chamberTiles[target]->isCharachter()) {
        chamberTiles[target]->getObject()->beAttacked(c, chamberTiles[target]->getObject());
        Action << c->getAction();
        
        killIfDead(target);
    }

}

void Chamber::scanAttack(std::shared_ptr<Object> c) {
    int location = locate(c);
    if (location == -1) return;

    std::istringstream iss {"no so ea we ne nw se sw"};
    std::string s;
    while (iss >> s) {
        int target = findTarget(location, s);
        if (target != -1 && chamberTiles[target]->getTile() == '@') {
            attack(c, s);
            return;
        }
    }
}

void Chamber::use(std::shared_ptr<Object> c, std::string dir) {
    int location = locate(c);
    if (location == -1) return;

    int target = findTarget(location, dir);
    if (target == -1) return;

    if (chamberTiles[target]->isItem()) {
        chamberTiles[target]->getObject()->beUsed(c, chamberTiles[target]->getObject());
        Action << c->getAction();
        Action << chamberTiles[target]->getObject()->getAction();
        killIfDead(target);
    }

}

std::string Chamber::getAction() {
    return Action.str();
}

void Chamber::actionReset() {
    Action.str("");
}

void Chamber::debugPrintChamber() {
    for (int i = 0; i < height; i++) {
        int displacement = i * width;
        for (int j = 0; j < width; j++) {
            std::cout << chamberTiles[j + displacement]->getTile();
        }
        std::cout << std::endl;
    }
}
