//
// Created by Satyamedh on 15-11-2025.
//

#ifndef NPORTAL_InputController_H
#define NPORTAL_InputController_H

#include <libndls.h>
#include <cstddef>

//typedef struct {
//    unsigned char contact; /* "touched". TRUE or FALSE */
//    unsigned char proximity;
//    uint16_t x;
//    uint16_t y;
//    unsigned char x_velocity;
//    unsigned char y_velocity;
//    uint16_t dummy;
//    unsigned char pressed; /* "key pressed". TRUE or FALSE */
//    unsigned char arrow; /* area of the pad currently touched. see tpad_arrow_t. */
//} touchpad_report_t;


#ifdef isKeyPressed
#undef isKeyPressed
#endif

class InputController {
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
        SwitchWorld,
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


#endif //NPORTAL_InputController_H
