
#include "entity.hpp"

Entity::Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath, TTF_Font* font, bool debug) {
	rnd = renderer;
	control = ctrl;
	this->font = font;
	this->debug = debug;
	if (!sprite.loadFromFile(rnd, spritePath))
		std::cerr << "Entity error: Could not load sprite: '" << spritePath << "'\n";
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
	sprite.render({16 * frameIndex, 0, control->w, control->h}, rx, ry, flip);

	if (debug)
		renderDebug(rx, ry);
}

void Entity::renderDebug (int rx, int ry) {
	SDL_Color color = {255, 0, 0};
	debugText.loadFromText(rnd, font, &color, control->getDebugString());
	debugText.render(rx + control->w + 8, ry);
}

Box Entity::getBoundingBox () {
	return {(int)control->x, (int)control->y, control->w, control->h};
}

void Entity::update (float delta) {
	control->update(delta);
}
