//
// Created by Satyamedh on 18-11-2025.
//

#ifndef NPORTAL_PLAYERCONTROLLER_H
#define NPORTAL_PLAYERCONTROLLER_H

#include "../InputController//InputController.h"
#include "../GameState/GameState.h"
#include "../Settings/Settings.h"

class PlayerController {
public:
    void init(GameState* gs, InputController* inp);

    void update(float deltaTime);

private:
    // reference to the player entity and input controller
    GameState* gameState;
    InputController* input;

};


#endif //NPORTAL_PLAYERCONTROLLER_H
