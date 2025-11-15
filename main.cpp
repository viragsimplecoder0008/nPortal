#include <libndls.h>
#include "components/PlayerInput/PlayerInput.h"
#include <os.h>

int main(){

    PlayerInput input;
    while (true) {
        input.pollInput();
        printf("Forward key is %s\n", PlayerInput::isDown(PlayerInput::Key::Forward) ? "pressed" : "not pressed");
        msleep(500); // Sleep for 500 milliseconds
    }
    return 0;

}