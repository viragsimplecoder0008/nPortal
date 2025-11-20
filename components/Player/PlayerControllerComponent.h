#pragma once

#include "../ECS/Component.h"
#include "../InputController/InputController.h"
#include "../Settings/Settings.h"
#include "../../nGL/fastmath.h"
#include <algorithm>

class PlayerControllerComponent : public Component {
public:
    void Init(InputController* inp) {
        this->input = inp;
    }

    void Update(float deltaTime) override;

private:
    InputController* input = nullptr;

    bool tp_had_contact = false;
    uint16_t tp_last_x = 0;
    uint16_t tp_last_y = 0;
};
