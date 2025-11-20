//
// Created by Satyamedh on 15-11-2025.
//

#include "InputController.h"

const InputController::KeyMapping InputController::keyMappings[] = {
        { Key::Forward,   &KEY_NSPIRE_8 },
        { Key::Backward,  &KEY_NSPIRE_2 },
        { Key::Left,      &KEY_NSPIRE_4 },
        { Key::Right,     &KEY_NSPIRE_6 },
        { Key::Jump,      &KEY_NSPIRE_VAR },
        { Key::Crouch,    &KEY_NSPIRE_SHIFT },
        { Key::Escape,    &KEY_NSPIRE_ESC },
        { Key::Interact,  &KEY_NSPIRE_DEL },
        { Key::SwitchWorld, &KEY_NSPIRE_5 } // Using 5 for switch, since 6 is Right. User asked for 6 but it conflicts.
};

// initialize static member
bool InputController::keyStates[static_cast<std::size_t>(InputController::Key::Unknown) + 1] = { false };

bool InputController::keysEqual(const t_key &lhs, const t_key &rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col &&
           lhs.tpad_row == rhs.tpad_row && lhs.tpad_col == rhs.tpad_col &&
           lhs.tpad_arrow == rhs.tpad_arrow;
}

InputController::Key InputController::fromPortalKey(const t_key &ndKey) {
    for (const KeyMapping &mapping : keyMappings) {
        if (keysEqual(*mapping.ndKey, ndKey)) {
            return mapping.gameKey;
        }
    }
    return Key::Unknown;
}

const t_key &InputController::toPortalKey(Key key) {
    for (const KeyMapping &mapping : keyMappings) {
        if (mapping.gameKey == key) {
            return *mapping.ndKey;
        }
    }
    return KEY_NSPIRE_ESC;
}

bool InputController::pollInput() {
    // check if any key we track has changed state
    bool anyChanged = false;
    for (const KeyMapping &mapping : keyMappings) {
        bool currentlyPressed = isKeyPressed(mapping.ndKey);
        auto index = static_cast<std::size_t>(mapping.gameKey);
        if (keyStates[index] != currentlyPressed) {
            keyStates[index] = currentlyPressed;
            anyChanged = true;
        }
    }
    touchpad_report_t newTouchpad;
    touchpad_scan(&newTouchpad);

    /*
     * Touchpad input is read into a touchpad_report_t structure that contains:

    contact - whether the touchpad is being touched
    x and y coordinates of the touch
    x_velocity and y_velocity
    pressed - whether a key is pressed
    arrow - which arrow area of the pad is touched
     */

    if (touchpad.contact != newTouchpad.contact ||
        touchpad.x != newTouchpad.x ||
        touchpad.y != newTouchpad.y ||
        touchpad.x_velocity != newTouchpad.x_velocity ||
        touchpad.y_velocity != newTouchpad.y_velocity ||
        touchpad.pressed != newTouchpad.pressed ||
        touchpad.arrow != newTouchpad.arrow) {
            touchpad = newTouchpad;
            anyChanged = true;
    }

    return anyChanged;
}

bool InputController::isDown(InputController::Key key) {
    auto index = static_cast<std::size_t>(key);
    const std::size_t keyStatesCount = sizeof(keyStates) / sizeof(keyStates[0]);
    if (index >= keyStatesCount) {
        return false;
    }
    return keyStates[index];
}
