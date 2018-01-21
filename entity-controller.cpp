
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
    gravity = 0;
    direction = true;
}

void EntityController::setGravity (float gravity) {
    this->gravity = gravity;
}

std::string EntityController::getDebugString () {
    const char* EntityStateStrings[] = {
        "ENTITY_IDLE", "ENTITY_JUMPING", "ENTITY_RUNNING", "ENTITY_FLYING",
        "ENTITY_FLYING_UNCONSCIOUS", "ENTITY_CLIMBING", "ENTITY_CLIMBING_IDLE",
        "ENTITY_CLIMBING_JUMPING", "ENTITY_UNCONSCIOUS", "ENTITY_DEAD"
    };
    std::stringstream str;
    str << EntityStateStrings[state] << ' ' << (int)round(vy);
    return str.str();
}
