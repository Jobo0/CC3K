#include <iostream>
#include <string>
#include <memory>


#include "gameManager.h"
#include "textCommands.h"
#include <string>

// 79 x 25 display

int main(int argc, char *argv[]){ // ARGUMENTS: (FILENAME) (SEED) or (SEED) or (FILENAME)
    std::shared_ptr<GameManager> game;
    std::shared_ptr<TextCommands> gameInput;

    bool firstIsSeed = true;
    std::string fileName;
    if (argc > 1) {
        try {
			std::stoi( std::string{ argv[1] } ); // if first argument is not a seed
		} catch( ... ) {
            fileName = std::string{argv[1]};
            firstIsSeed = false;
		}
        if (firstIsSeed) {
            game = std::make_shared<GameManager>(argv[1]);
        } else {
            if (argc > 2) {
                game = std::make_shared<GameManager>(argv[2]);
            } else {
                game = std::make_shared<GameManager>();
            }
        }
    } else {
        game = std::make_shared<GameManager>();
    }
    if (!firstIsSeed) {
        gameInput = std::make_shared<TextCommands>(game, fileName);
    } else {
        gameInput = std::make_shared<TextCommands>(game);
    }
    
    gameInput->start();
}
