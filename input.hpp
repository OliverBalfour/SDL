
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

enum InputType {
    KEYDOWN_INPUT,
    KEYUP_INPUT,
    MOUSEMOTION_INPUT,
    MOUSEBUTTONDOWN_INPUT,
    MOUSEBUTTONUP_INPUT
};

struct KeyboardInput {
    InputType type;
    SDL_Keycode key;
};
struct MouseMotionInput {
    InputType type;
    int x, y, xrel, yrel;
};
struct MouseClickInput {
    InputType type;
    unsigned short button;
};

union Input {
    InputType type;
    KeyboardInput key;
    MouseMotionInput motion;
    MouseClickInput button;
};

#endif
