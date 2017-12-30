
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <iostream>
#include <vector>

#include <SDL.h>

#include "entity-controller.hpp"

struct Mouse {
	unsigned short int x, y;
	bool leftButton, rightButton, middleButton;
};

class PlayerController : public EntityController {
    public:
        PlayerController (std::vector<bool>* kys, Mouse* ms);
        void update ();
    private:
        std::vector<bool>* keys;
        Mouse* mouse;
        void stateIdle ();
        void stateJumping ();
        void stateRunning ();
        void stateFlying ();
        void stateFlyingUnconscious ();
        void stateClimbing ();
        void stateClimbingIdle ();
        void stateClimbingJumping ();
        void stateUnconscious ();
        void stateDead ();
};

#endif
