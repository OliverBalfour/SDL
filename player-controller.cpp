
#include "player-controller.hpp"

PlayerController::PlayerController (std::vector<bool>* kys, Mouse* ms) {
	keys = kys;
	mouse = ms;
}

void PlayerController::stateIdle (float delta) {}
void PlayerController::stateJumping (float delta) {}
void PlayerController::stateRunning (float delta) {
	vx = runningSpeed;
	if (direction)
		dx = delta * vx;
	else
		dx = delta * -vx;
}
void PlayerController::stateFlying (float delta) {
	vy += gravity * delta;
	vx *= 1 - (0.1 * delta);
	dx = delta * vx;
	dy = delta * vy;
}
void PlayerController::stateFlyingUnconscious (float delta) {}
void PlayerController::stateClimbing (float delta) {}
void PlayerController::stateClimbingIdle (float delta) {}
void PlayerController::stateClimbingJumping (float delta) {}
void PlayerController::stateUnconscious (float delta) {}
void PlayerController::stateDead (float delta) {}

void PlayerController::update (float delta) {
	switch (state) {
		case ENTITY_IDLE:
			stateIdle(delta); break;
		case ENTITY_JUMPING:
			stateJumping(delta); break;
		case ENTITY_RUNNING:
			stateRunning(delta); break;
		case ENTITY_FLYING:
			stateFlying(delta); break;
		case ENTITY_FLYING_UNCONSCIOUS:
			stateFlyingUnconscious(delta); break;
		case ENTITY_CLIMBING:
			stateClimbing(delta); break;
		case ENTITY_CLIMBING_IDLE:
			stateClimbingIdle(delta); break;
		case ENTITY_CLIMBING_JUMPING:
			stateClimbingJumping(delta); break;
		case ENTITY_UNCONSCIOUS:
			stateUnconscious(delta); break;
		case ENTITY_DEAD:
			stateDead(delta); break;
	}
}

void PlayerController::onNotify (const Input& input) {
	// press key to change direction
	if (input.type == KEYDOWN_INPUT && input.key.key == SDLK_a)
		direction = 0;
	else if (input.type == KEYDOWN_INPUT && input.key.key == SDLK_d)
		direction = 1;
	// release key to revert direction
	else if (input.type == KEYUP_INPUT && input.key.key == SDLK_a && keys->at(SDLK_d))
		direction = 1;
	else if (input.type == KEYUP_INPUT && input.key.key == SDLK_d && keys->at(SDLK_a))
		direction = 0;

	// press A/D to start running
	if (input.type == KEYDOWN_INPUT && (input.key.key == SDLK_a || input.key.key == SDLK_d) && state == ENTITY_IDLE)
		{ state = ENTITY_RUNNING; direction = input.key.key == SDLK_d; startTicks = SDL_GetTicks(); }
	// press A/D to start climbing (as opposed to climbing_idle)
	else if (input.type == KEYDOWN_INPUT && (input.key.key == SDLK_a || input.key.key == SDLK_d) && state == ENTITY_CLIMBING_IDLE)
		{ state = ENTITY_CLIMBING; direction = input.key.key == SDLK_d; startTicks = SDL_GetTicks(); }
	// press A/D to start running
	else if (input.type == KEYUP_INPUT && (input.key.key == SDLK_a || input.key.key == SDLK_d) && !keys->at(SDLK_a) && !keys->at(SDLK_d) && state == ENTITY_RUNNING)
		state = ENTITY_IDLE;
	// press A/D to start climbing (as opposed to climbing_idle)
	else if (input.type == KEYUP_INPUT && (input.key.key == SDLK_a || input.key.key == SDLK_d) && !keys->at(SDLK_a) && !keys->at(SDLK_d) && state == ENTITY_CLIMBING)
		state = ENTITY_CLIMBING_IDLE;

	// left click to start jumping
	else if (input.type == MOUSEBUTTONDOWN_INPUT && input.button.button == SDL_BUTTON_LEFT && (state == ENTITY_IDLE || state == ENTITY_RUNNING))
		state = ENTITY_JUMPING;
	// left click to start climbing_jumping
	else if (input.type == MOUSEBUTTONDOWN_INPUT && input.button.button == SDL_BUTTON_LEFT && (state == ENTITY_CLIMBING_IDLE || state == ENTITY_CLIMBING))
		state = ENTITY_CLIMBING_JUMPING;
	// release left click to stop jumping and idle
	else if (input.type == MOUSEBUTTONUP_INPUT && input.button.button == SDL_BUTTON_LEFT && state == ENTITY_JUMPING)
		state = ENTITY_IDLE;
	// release left click to stop climbing_jumping and idle
	else if (input.type == MOUSEBUTTONUP_INPUT && input.button.button == SDL_BUTTON_LEFT && state == ENTITY_CLIMBING_JUMPING)
		state = ENTITY_CLIMBING_IDLE;

	// press key to start flying
	else if (input.type == KEYDOWN_INPUT && input.key.key == SDLK_SPACE && (state == ENTITY_IDLE || state == ENTITY_RUNNING)) {
		state = ENTITY_FLYING;
		vy = -160;
		vx = runningSpeed * (direction ? 1 : -1);
	}
}
