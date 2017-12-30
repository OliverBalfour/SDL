
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "entity-controller.hpp"

class PlayerController : public EntityController {
    public:
        EntityState update (EntityState);
    private:
        void stateIdle ();
        void stateJumping ();
        void stateRunning ();
        void stateFlying ();
        void stateFlyingUnconscious ();
        void stateClimbing ();
        void stateClimbingIdle ();
        void stateClimbingJumping ();
        void stateUnconscious ();
        void stateDead ();
};

#endif
