//
// Created by Satyamedh on 15-11-2025.
//

#ifndef NPORTAL_PLAYERINPUT_H
#define NPORTAL_PLAYERINPUT_H

#include <libndls.h>
#include <cstddef>

#ifdef isKeyPressed
#undef isKeyPressed
#endif

class PlayerInput {
public:
    enum class Key {
        Forward,
        Backward,
        Left,
        Right,
        Jump,
        Crouch,
        Escape,
        Interact,
        Unknown
    };

    static Key fromPortalKey(const t_key &ndKey);
    static const t_key &toPortalKey(Key key);
    static bool isDown(Key key);
    touchpad_report_t touchpad;

    bool pollInput();

private:
    struct KeyMapping {
        Key gameKey;
        const t_key *ndKey;
    };

    static bool keysEqual(const t_key &lhs, const t_key &rhs);
    static bool keyStates[static_cast<std::size_t>(Key::Unknown) + 1];
    static const KeyMapping keyMappings[];
    static constexpr std::size_t keyMappingCount = 8;
};


#endif //NPORTAL_PLAYERINPUT_H
