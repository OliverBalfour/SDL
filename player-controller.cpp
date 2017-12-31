
#include "player-controller.hpp"

PlayerController::PlayerController (std::vector<bool>* kys, Mouse* ms) {
    keys = kys;
    mouse = ms;
}

void PlayerController::stateIdle () {}
void PlayerController::stateJumping () {}
void PlayerController::stateRunning () {
    if (direction)
        x += 2;
    else
        x -= 2;
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

void PlayerController::onNotify (unsigned int event, unsigned int data) {
    // press key to change direction
    if (event == SDL_KEYDOWN && data == SDLK_a)
        direction = 0;
    else if (event == SDL_KEYDOWN && data == SDLK_d)
        direction = 1;
    // release key to revert direction
    else if (event == SDL_KEYUP && data == SDLK_a && keys->at(SDLK_d))
        direction = 1;
    else if (event == SDL_KEYUP && data == SDLK_d && keys->at(SDLK_a))
        direction = 0;

    // press A/D to start running
    if (event == SDL_KEYDOWN && (data == SDLK_a || data == SDLK_d) && state == ENTITY_IDLE)
        { state = ENTITY_RUNNING; direction = data == SDLK_d; startTicks = SDL_GetTicks(); }
    // press A/D to start climbing (as opposed to climbing_idle)
    else if (event == SDL_KEYDOWN && (data == SDLK_a || data == SDLK_d) && state == ENTITY_CLIMBING_IDLE)
        { state = ENTITY_CLIMBING; direction = data == SDLK_d; startTicks = SDL_GetTicks(); }
    // press A/D to start running
    else if (event == SDL_KEYUP && (data == SDLK_a || data == SDLK_d) && !keys->at(SDLK_a) && !keys->at(SDLK_d) && state == ENTITY_RUNNING)
        state = ENTITY_IDLE;
    // press A/D to start climbing (as opposed to climbing_idle)
    else if (event == SDL_KEYUP && (data == SDLK_a || data == SDLK_d) && !keys->at(SDLK_a) && !keys->at(SDLK_d) && state == ENTITY_CLIMBING)
        state = ENTITY_CLIMBING_IDLE;
    // left click to start jumping
    else if (event == SDL_MOUSEBUTTONDOWN && data == SDL_BUTTON_LEFT && (state == ENTITY_IDLE || state == ENTITY_RUNNING))
        state = ENTITY_JUMPING;
    // left click to start climbing_jumping
    else if (event == SDL_MOUSEBUTTONDOWN && data == SDL_BUTTON_LEFT && (state == ENTITY_CLIMBING_IDLE || state == ENTITY_CLIMBING))
        state = ENTITY_CLIMBING_JUMPING;
    // release left click to stop jumping and idle
    else if (event == SDL_MOUSEBUTTONUP && data == SDL_BUTTON_LEFT && state == ENTITY_JUMPING)
        state = ENTITY_IDLE;
    // release left click to stop climbing_jumping and idle
    else if (event == SDL_MOUSEBUTTONUP && data == SDL_BUTTON_LEFT && state == ENTITY_CLIMBING_JUMPING)
        state = ENTITY_CLIMBING_IDLE;
}
