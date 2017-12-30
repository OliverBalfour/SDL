
void PlayerController::update () {
    switch (entity->state) {
        case ENTITY_IDLE:
            stateIdle(); break;
        case ENTITY_JUMPING:
            stateJumping(); break;
        case ENTITY_RUNNING:
            stateRunning(); break;
        case ENTITY_FLYING:
            stateFlying(); break;
        case ENTITY_FLYING_UNCONSCIOUS:
            stateFlyingUnconscious(); break;
        case ENTITY_CLIMBING:
            stateClimbing(); break;
        case ENTITY_CLIMBING_IDLE:
            stateClimbingIdle(); break;
        case ENTITY_CLIMBING_JUMPING:
            stateClimbingJumping(); break;
        case ENTITY_UNCONSCIOUS:
            stateUnconscious(); break;
        case ENTITY_DEAD:
            stateDead(); break;
    }
}

void stateIdle () {
    ;
}
