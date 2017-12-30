
#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>

#include "texture.hpp"
#include "entity-controller.hpp"

class Entity {
    public:
        Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath);
        void render ();
        void update ();
    private:
        unsigned short int x;
        unsigned short int y;
        bool direction; // true is right (or down, when climbing)
        Texture sprite;
        EntityController* control;
        EntityState state;
};

#endif
