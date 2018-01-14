
#include "entity-controller.hpp"

EntityController::EntityController () {
    state = ENTITY_JUMPING;
    x = 100;
    y = 0;
	w = 16;
	h = 32;
	dx = 0;
	dy = 0;
    vx = 0;
    vy = 120;
    direction = true;
}
