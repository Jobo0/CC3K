#include "objectCreator.h"
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "./Player/human.h"
#include "./Player/elf.h"
#include "./Player/dwarf.h"
#include "./Player/orc.h"
#include "gold.h"
#include "./Enemy/vampire.h"
#include "./Enemy/werewolf.h"
#include "./Enemy/troll.h"
#include "./Enemy/phoenix.h"
#include "./Enemy/goblin.h"
#include "./Enemy/dragon.h"
#include "./Enemy/merchant.h"


ObjectCreator::ObjectCreator(char pRace): playerRace{pRace} {
    
};  

std::shared_ptr<Object> ObjectCreator::createFromChar(char c) {
    if (c == '@') {
        if (playerRace == 'e') {
            return std::make_shared<Elf>();
        } else if (playerRace == 'd') {
            return std::make_shared<Dwarf>();
        } else if (playerRace == 'o') {
            return std::make_shared<Orc>();
        } else {
            return std::make_shared<Human>();
        }
    }

    if (c == 'V' || c == 'W' || c == 'T' || c == 'N' || c == 'M' || c == 'D' || c == 'X' ) {
        if (c == 'V') {
            return std::make_shared<Vampire>();
        } else if (c == 'W') {
            return std::make_shared<Werewolf>();
        } else if (c == 'T') {
            return std::make_shared<Troll>();
        } else if (c == 'N') {
            return std::make_shared<Goblin>();
        } else if (c == 'M') {
            return std::make_shared<Merchant>();
        } else if (c == 'D') {
            return std::make_shared<Dragon>();
        } else if (c == 'X') {
            return std::make_shared<Dragon>();
        }
    }

    if (c == '6' || c == '7' || c == '8' || c == '9') {
        if (c == '6') {
            return std::make_shared<Gold>(1);
        } else if (c == '7') {
            return std::make_shared<Gold>(2);
        } else if (c == '8') {
            return std::make_shared<Gold>(4);
        } else if (c == '9') {
            return std::make_shared<Gold>(6);
        }
    }



    return nullptr; // actually should never make just an "object", also replace object constructor
}
