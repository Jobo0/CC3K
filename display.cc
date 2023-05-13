#include "display.h"
#include "level.h"
#include <iostream>
#include <sstream>
#include <string>

Display::Display(int width, int height): width{width}, height{height} {};

void Display::notify(Level &level) {
    for (int i = 0; i < height; i++) {
        int displacement = i * width;
        for (int j = 0; j < width; j++) {
            char c;
            c = level.getStateRef()[j + displacement]->getTile();
            if (c == '@') {
                std::cout << "\033[1;32m" << c << "\033[0m";
            } else if (c == 'V' || c == 'W' || c == 'T' || c == 'N' || c == 'M' || c == 'D' || c == 'X' ) {
                std::cout << "\033[1;35m" << c << "\033[0m";
            } else if (c == 'G') {
                std::cout << "\033[1;33m" << c << "\033[0m";
            } else {
                std::cout << c;
            }
        }
        std::cout << std::endl;
    }

    std::string info = level.getPlayerInfo();
    std::istringstream iss {info};

    char R = level.getPlayerRace();
    std::cout << "Race: ";
    if (R == 'h') {
        std::cout << "Human";
    } else if (R == 'e') {
        std::cout << "Elf";
    } else if (R == 'd') {
        std::cout << "Dwarf";
    } else if (R == 'o') {
        std::cout << "Orc";
    }
    std::string atk;
    std::string def;
    std::string hp;
    std::string gold;
    iss >> atk;
    iss >> def;
    iss >> hp;
    iss >> gold;

    std::cout << " | Gold: " << gold << std::endl;

    std::cout << "HP: " << hp << std::endl;
    std::cout << "ATK: " << atk << std::endl;
    std::cout << "DEF: " << def << std::endl;

    if (std::stoi(hp) <= 0) {
        std::cout << "Action: Game Over." << std::endl;
    } else {
        std::cout << "Action: " << level.getAction() << std::endl;
    }
    

};
