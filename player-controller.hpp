
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>

#include "entity-controller.hpp"
#include "observer.hpp"
#include "input.hpp"

struct Mouse {
	unsigned short int x, y;
	bool leftButton, rightButton, middleButton;
};

class PlayerController : public EntityController, public Observer {
	public:
		PlayerController (std::vector<bool>* kys, Mouse* ms);
		void update (float delta);
		void onNotify (const Input& input);
	private:
		std::vector<bool>* keys;
		Mouse* mouse;
		void stateIdle (float delta);
		void stateJumping (float delta);
		void stateRunning (float delta);
		void stateFlying (float delta);
		void stateFlyingUnconscious (float delta);
		void stateClimbing (float delta);
		void stateClimbingIdle (float delta);
		void stateClimbingJumping (float delta);
		void stateUnconscious (float delta);
		void stateDead (float delta);
};

#endif
