
#include "entity-controller.hpp"

EntityController::EntityController () {
    state = ENTITY_IDLE;
    x = 0;
    y = 0;
    direction = true;
}
