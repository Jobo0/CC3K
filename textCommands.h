#ifndef TEXT_COMMANDS_H
#define TEXT_COMMANDS_H

#include <memory>
#include <string>

class GameManager;

class TextCommands {
    std::shared_ptr<GameManager> game;
    std::string loadFileName;
    public:
    TextCommands(std::shared_ptr<GameManager> g);
    TextCommands(std::shared_ptr<GameManager> g, std::string fileName);
    void start();
};

#endif
