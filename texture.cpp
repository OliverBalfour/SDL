
#include "texture.hpp"

Texture::Texture () {
    texture = NULL;
	font = NULL;
	color = NULL;
	text = "";
    width = 0;
    height = 0;
}

Texture::~Texture () {
    unload();
}

bool Texture::loadFromFile (SDL_Renderer* rnd, string path) {
	unload();
    renderer = rnd;
    SDL_Surface* sf = IMG_Load(path.c_str());
    if (sf == NULL) {
        std::cerr << "SDL Error: Could not load image '" << path << "': " << IMG_GetError() << "\n";
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, sf);
    if (texture == NULL) {
        std::cerr << "SDL Error: Could not create texture '" << path << "': " << SDL_GetError() << "\n";
        return false;
    }
    width = sf->w;
    height = sf->h;
    SDL_FreeSurface(sf);
    return true;
}

bool Texture::loadFromText (SDL_Renderer* rnd, TTF_Font* fnt, SDL_Color* cl, string txt) {
	unload();
	renderer = rnd;
	font = fnt;
	color = cl;
	text = txt;

	SDL_Surface* sf = TTF_RenderText_Blended(font, text.c_str(), *color);
	if (sf == NULL) {
		std::cerr << "SDL_ttf error: Could not render text surface: " << TTF_GetError() << "\n";
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, sf);
	if (texture == NULL) {
        std::cerr << "SDL Error: Could not create text texture: " << SDL_GetError() << "\n";
        return false;
    }
    width = sf->w;
    height = sf->h;
    SDL_FreeSurface(sf);
    return true;
}

void Texture::unload () {
    if (texture) {
        SDL_DestroyTexture(texture);
		renderer = NULL;
        texture = NULL;
		font = NULL;
		color = NULL;
		text = "";
        width = 0;
        height = 0;
    }
}

void Texture::render (int x, int y) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void Texture::render (int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Texture::render (SDL_Rect clip, int x, int y) {
    SDL_Rect rect = {x, y, clip.w, clip.h};
    SDL_RenderCopy(renderer, texture, &clip, &rect);
}
void Texture::render (SDL_Rect clip, int x, int y, float scale) {
    SDL_Rect rect = {x, y, int(clip.w * scale), int(clip.h * scale)};
    SDL_RenderCopy(renderer, texture, &clip, &rect);
}

int Texture::getWidth () { return width; }
int Texture::getHeight () { return height; }
