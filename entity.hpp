
#ifndef ENTITY_H
#define ENTITY_H

#include "texture.hpp"
#include "entity-controller.hpp"

class Entity {
    public:
        Entity (EntityController* ctrl, std::string spritePath);
        void render ();
        void update ();
    private:
        unsigned short int x;
        unsigned short int y;
        bool direction; // true is right (or down, when climbing)
        Texture sprite;
        friend class EntityController;
        EntityController* control;
        EntityState state;
};

#endif
