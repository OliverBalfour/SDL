
#include "entity-controller.hpp"

EntityController::EntityController () {
    state = ENTITY_IDLE;
    x = 100;
    y = 0;
	w = 16;
	h = 32;
	dx = 0;
	dy = 0;
    direction = true;
}
