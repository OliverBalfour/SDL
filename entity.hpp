
#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>

#include <SDL.h>

#include "texture.hpp"
#include "entity-controller.hpp"

class Entity {
    public:
        Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath);
        void render ();
        void update (float delta);
    private:
        Texture sprite;
        EntityController* control;
};

#endif
