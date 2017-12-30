
Entity::Entity (EntityController* ctrl, std::string spritePath) {
    state = ENTITY_IDLE;
    x = 0;
    y = 0;
    direction = true;
    sprite.loadFromFile(spritePath);
    control = ctrl;
    control->bindEntity(this);
}

void Entity::render () {
    unsigned short int frameIndex;
    if (state == ENTITY_IDLE)
        frameIndex = 0;
    else if (state == ENTITY_RUNNING && direction)
        frameIndex = 1;
    else if (state == ENTITY_RUNNING && !direction)
        frameIndex = 2;
    sprite.render({16 * frameIndex, 0, 16, 32}, x, y, 2.0f);
}

void Entity::update () {
    control->update();
}
