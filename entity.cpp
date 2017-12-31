
#include "entity.hpp"

Entity::Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath) {
    if (!sprite.loadFromFile(renderer, spritePath))
        std::cerr << "Entity error: Could not load sprite: '" << spritePath << "'\n";
    control = ctrl;
}

void Entity::render () {
    unsigned short int frameIndex;
    SDL_RendererFlip flip = control->direction ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if (control->state == ENTITY_IDLE)
        frameIndex = 0;
    else if (control->state == ENTITY_RUNNING) {
        unsigned int ticks = SDL_GetTicks();
        if ((ticks - ticks % 500) % 1000 == 0)
            frameIndex = 1;
        else frameIndex = 2;
    }
    sprite.render({16 * frameIndex, 0, 16, 32}, control->x, control->y, 2.0f, flip);
}

void Entity::update () {
    control->update();
}
