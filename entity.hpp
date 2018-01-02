
#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>

#include <SDL.h>

#include "texture.hpp"
#include "entity-controller.hpp"

class Map;

class Entity {
    public:
        Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath);
        void render (int ox, int oy); //offset x and y
        void update (float delta);
        void getSize (int* w, int* h);
    private:
        friend class Map;
        Texture sprite;
        EntityController* control;
};

#endif
