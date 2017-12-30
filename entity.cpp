
#include "entity.hpp"

Entity::Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath) {
    state = ENTITY_IDLE;
    x = 0;
    y = 0;
    direction = true;
    if (!sprite.loadFromFile(renderer, spritePath))
        std::cerr << "Entity error: Could not load sprite: " << spritePath << "\n";
    control = ctrl;
}

void Entity::render () {
    unsigned short int frameIndex;
    if (state == ENTITY_IDLE)
        frameIndex = 0;
    else if (state == ENTITY_RUNNING && direction)
        frameIndex = 1;
    else if (state == ENTITY_RUNNING && !direction)
        frameIndex = 2;
    sprite.render({16 * frameIndex, 0, 16, 32}, x, y, 2.0f);
}

void Entity::update () {
    state = control->update(state);
}
