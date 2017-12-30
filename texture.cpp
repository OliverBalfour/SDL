
#include "texture.hpp"

Texture::Texture () {
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture () {
    unload();
}

bool Texture::loadFromFile (SDL_Renderer* rnd, string path) {
    renderer = rnd;
    unload();
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

void Texture::unload () {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL;
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
    SDL_Rect rect = {x, y, clip.w * scale, clip.h * scale};
    SDL_RenderCopy(renderer, texture, &clip, &rect);
}

int Texture::getWidth () { return width; }
int Texture::getHeight () { return height; }
