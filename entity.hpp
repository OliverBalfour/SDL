
#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>

#include <SDL.h>
#include <SDL_ttf.h>

#include "texture.hpp"
#include "entity-controller.hpp"
#include "box.hpp"

class Map;

class Entity {
	public:
		Entity (EntityController* ctrl, SDL_Renderer* renderer, std::string spritePath, TTF_Font* font, bool debug = false);
		void render (int ox, int oy); //offset x and y
		void update (float delta);
		Box getBoundingBox ();
	private:
		void renderDebug (int rx, int ry);
		friend class Map;
		Texture sprite;
		Texture debugText;
		TTF_Font* font;
		EntityController* control;
		SDL_Renderer* rnd;
		bool debug;
};

#endif
