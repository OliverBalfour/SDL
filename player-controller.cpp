
#include "player-controller.hpp"

PlayerController::PlayerController (std::vector<bool>* kys, Mouse* ms) {
    keys = kys;
    mouse = ms;
}

void PlayerController::stateIdle () {
    if (keys->at(SDLK_d)) {
        direction = 1;
        state = ENTITY_RUNNING;
    } else if (keys->at(SDLK_a)) {
        direction = 0;
        state = ENTITY_RUNNING;
    }
}
void PlayerController::stateJumping () {}
void PlayerController::stateRunning () {
    if (direction) x += 2;
    else x -= 2;

    if (keys->at(SDLK_d)) {
        direction = 1;
	} else if (keys->at(SDLK_a)) {
        direction = 0;
    } else {
        state = ENTITY_IDLE;
    }
}
void PlayerController::stateFlying () {}
void PlayerController::stateFlyingUnconscious () {}
void PlayerController::stateClimbing () {}
void PlayerController::stateClimbingIdle () {}
void PlayerController::stateClimbingJumping () {}
void PlayerController::stateUnconscious () {}
void PlayerController::stateDead () {}

void PlayerController::update () {
    switch (state) {
        case ENTITY_IDLE:
            stateIdle(); break;
        case ENTITY_JUMPING:
            stateJumping(); break;
        case ENTITY_RUNNING:
            stateRunning(); break;
        case ENTITY_FLYING:
            stateFlying(); break;
        case ENTITY_FLYING_UNCONSCIOUS:
            stateFlyingUnconscious(); break;
        case ENTITY_CLIMBING:
            stateClimbing(); break;
        case ENTITY_CLIMBING_IDLE:
            stateClimbingIdle(); break;
        case ENTITY_CLIMBING_JUMPING:
            stateClimbingJumping(); break;
        case ENTITY_UNCONSCIOUS:
            stateUnconscious(); break;
        case ENTITY_DEAD:
            stateDead(); break;
    }
}
