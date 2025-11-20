//
// Created by Satyamedh on 18-11-2025.
//

#ifndef NPORTAL_GAMESTATE_H
#define NPORTAL_GAMESTATE_H

#include <string>
#include <memory>

#include "../../nGL/gl.h"
#include "../../nGL/fastmath.h"
#include "../Player/Player.h"

class GameState {
public:
    std::unique_ptr<Player> player;
    std::string currentLevel;

    void init();

};


#endif //NPORTAL_GAMESTATE_H
