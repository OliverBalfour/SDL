
#include "entity.hpp"

Entity::Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath) {
    if (!sprite.loadFromFile(renderer, spritePath))
        std::cerr << "Entity error: Could not load sprite: '" << spritePath << "'\n";
    control = ctrl;
}

void Entity::render (int ox, int oy) {
    unsigned short int frameIndex;
    SDL_RendererFlip flip = control->direction ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    if (control->state == ENTITY_IDLE)
        frameIndex = 0;
    else if (control->state == ENTITY_RUNNING) {
        unsigned int ticks = SDL_GetTicks() - control->startTicks;
        if ((ticks - ticks % 500) % 1000 == 0)
            frameIndex = 1;
        else frameIndex = 2;
    }

    int rx = (int)round(control->x) + ox,
        ry = (int)round(control->y) + oy;
    sprite.render({16 * frameIndex, 0, 16, 32}, rx, ry, flip);
}

void Entity::getSize (int* w, int* h) {
    *w = 16;
    *h = 32;
}

void Entity::update (float delta) {
    control->update(delta);
}
