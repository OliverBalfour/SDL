
#ifndef ENTITY_CONTROLLER_H
#define ENTITY_CONTROLLER_H

#include <string>

// method of controlling an entity - can be a player, AI, or even networked player
// all it is responsible for doing is changing state
// example action source: keyboard/mouse, AI code, or TCP socket connection

// forward declaration
class Entity;

enum EntityState {
    ENTITY_IDLE, // Standing still. To running, flying, unconscious, dead
    ENTITY_JUMPING, // Preparing for a jump. To flying, idle, running, unconscious, dead
    ENTITY_RUNNING, // Running. To idle, flying, jumping, climbing, unconscious, dead
    ENTITY_FLYING, // Falling/jumping through open air. To climbing, idle, running, flying_unconscious
    ENTITY_FLYING_UNCONSCIOUS, // Falling/jumping through open air while unconscious/dead. To unconscious, dead
    ENTITY_CLIMBING, // Climbing up/down a wall. To climbing_idle, climbing_jumping, flying_unconscious
    ENTITY_CLIMBING_IDLE, // Hanging onto a wall. To climbing, climbing_jumping, flying_unconscious
    ENTITY_CLIMBING_JUMPING, // Preparing to jump off a wall. To flying, climbing_idle, climbing, flying_unconscious
    ENTITY_UNCONSCIOUS, // Knocked out. To dead
    ENTITY_DEAD // Dead. To nothing
}

class EntityController {
    public:
        EntityController ();
        void bindEntity (Entity* ent);
        virtual void update ();
    protected:
        Entity* entity;
};

#endif
