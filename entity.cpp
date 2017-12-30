
#include "entity.hpp"

Entity::Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath) {
    if (!sprite.loadFromFile(renderer, spritePath))
        std::cerr << "Entity error: Could not load sprite: '" << spritePath << "'\n";
    control = ctrl;
}

void Entity::render () {
    unsigned short int frameIndex;
    if (control->state == ENTITY_IDLE)
        frameIndex = 0;
    else if (control->state == ENTITY_RUNNING && control->direction)
        frameIndex = 1;
    else if (control->state == ENTITY_RUNNING && !control->direction)
        frameIndex = 2;
    sprite.render({16 * frameIndex, 0, 16, 32}, control->x, control->y, 2.0f);
}

void Entity::update () {
    control->update();
}
