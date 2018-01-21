
#include "entity-controller.hpp"

EntityController::EntityController () {
    state = ENTITY_FLYING;
    x = 96;
    y = 0;
	w = 16;
	h = 32;
	dx = 0;
	dy = 0;
    vx = 0;
    vy = 0;
	runningSpeed = 120;
    gravity = 0;
    direction = true;
}

void EntityController::setGravity (float gravity) {
    this->gravity = gravity;
}

std::string EntityController::getDebugString () {
    const char* EntityStateStrings[] = {
        "IDLE", "JUMPING", "RUNNING", "FLYING",
        "FLYING_UNCONSCIOUS", "CLIMBING", "CLIMBING_IDLE",
        "CLIMBING_JUMPING", "UNCONSCIOUS", "DEAD"
    };
    std::stringstream str;
    str << EntityStateStrings[state] << " vy" << (int)round(vy) << " y" << (int)round(y);
    return str.str();
}
