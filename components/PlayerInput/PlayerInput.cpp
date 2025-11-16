//
// Created by Satyamedh on 15-11-2025.
//

#include "PlayerInput.h"

const PlayerInput::KeyMapping PlayerInput::keyMappings[] = {
        { Key::Forward,   &KEY_NSPIRE_8 },
        { Key::Backward,  &KEY_NSPIRE_2 },
        { Key::Left,      &KEY_NSPIRE_LEFT },
        { Key::Right,     &KEY_NSPIRE_RIGHT },
        { Key::Jump,      &KEY_NSPIRE_5 },
        { Key::Crouch,    &KEY_NSPIRE_SHIFT },
        { Key::Escape,    &KEY_NSPIRE_ESC },
        { Key::Interact,  &KEY_NSPIRE_DEL }
};

// initialize static member
bool PlayerInput::keyStates[static_cast<std::size_t>(PlayerInput::Key::Unknown) + 1] = { false };

bool PlayerInput::keysEqual(const t_key &lhs, const t_key &rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col &&
           lhs.tpad_row == rhs.tpad_row && lhs.tpad_col == rhs.tpad_col &&
           lhs.tpad_arrow == rhs.tpad_arrow;
}

PlayerInput::Key PlayerInput::fromPortalKey(const t_key &ndKey) {
    for (const KeyMapping &mapping : keyMappings) {
        if (keysEqual(*mapping.ndKey, ndKey)) {
            return mapping.gameKey;
        }
    }
    return Key::Unknown;
}

const t_key &PlayerInput::toPortalKey(Key key) {
    for (const KeyMapping &mapping : keyMappings) {
        if (mapping.gameKey == key) {
            return *mapping.ndKey;
        }
    }
    return KEY_NSPIRE_ESC;
}

bool PlayerInput::pollInput() {
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
    return anyChanged;
}

bool PlayerInput::isDown(PlayerInput::Key key) {
    auto index = static_cast<std::size_t>(key);
    // Use portable sizeof-based array length instead of std::size (requires C++17)
    const std::size_t keyStatesCount = sizeof(keyStates) / sizeof(keyStates[0]);
    if (index >= keyStatesCount) {
        return false;
    }
    return keyStates[index];
}
