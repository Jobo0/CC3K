#include "textCommands.h"
#include "gameManager.h"

#include <iostream>
#include <string>

TextCommands::TextCommands(std::shared_ptr<GameManager> g): game{g}, loadFileName{""} {

}

TextCommands::TextCommands(std::shared_ptr<GameManager> g, std::string fileName): game{g}, loadFileName{fileName} {

}

void TextCommands::start() {

    bool gameStarted = false;

    std::cout << "Welcome to CC3K+" << std::endl;
    std::string cmd;
    while (std::cin) {
        if (gameStarted) {
        while (std::cin >> cmd) {
            if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
                game->enemiesAttack();
                game->movePlayer(cmd);
                game->actionStatus();
                game->enemiesMove();
            } 
             else if (cmd == "u") {
                std::string dir;
                std::cin >> dir;
                // could check if dir was inputted correctly so that false inputs dont result in a lost turn
                game->playerUse(dir);
                game->actionStatus();
            }
            else if (cmd == "a") {
                std::string dir;
                std::cin >> dir;
                // could check if dir was inputted correctly so that false inputs dont result in a lost turn
                game->playerAttack(dir);
                game->enemiesAttack();
                game->actionStatus();
                game->enemiesMove();
            }
            else if (cmd == "h" || cmd == "e" || cmd == "d" || cmd == "o") {

            }
            else if (cmd == "r") {
                gameStarted = false;
                game->resetLevel();
                break;
            }
            else if (cmd == "q") {
                return;
            }
            else {
                std::cout << "[Invalid Command]" << std::endl;
            }
            game->refresh();
            //std::cout << "[Enter Command:]" << std::endl;
            }
        } else {
            std::cout << "Choose a Race: (h)uman, (e)lf, (d)warf, (o)rc" << std::endl;
            while (std::cin >> cmd) {
                if (cmd == "h" || cmd == "e" || cmd == "d" || cmd == "o") {
                    gameStarted = true;
                    char r = cmd.at(0);
                    game->chooseRace(r);
                    if (loadFileName.length() > 0) {
                        game->loadFile(loadFileName);
                    } else {
                        game->loadFile("leveltest2.txt"); // EITHER LOAD FILE OR GENERATE LEVEL, TEMP WILL STILL LOAD FILE
                    }
                    game->actionStatus();
                    game->refresh();
                    break;
                } else {
                    std::cout << "[Invalid Race]" << std::endl;
                }
            }
        }
    }
}




