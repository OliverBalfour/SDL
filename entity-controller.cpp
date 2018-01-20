
#include "entity-controller.hpp"

EntityController::EntityController () {
    state = ENTITY_FLYING;
    x = 100;
    y = 0;
	w = 16;
	h = 32;
	dx = 0;
	dy = 0;
    vx = 0;
    vy = 0;
    gravity = 0;
    direction = true;
}

void EntityController::setGravity (float gravity) {
    this->gravity = gravity;
}
