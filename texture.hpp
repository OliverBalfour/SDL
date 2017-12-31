
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using std::string;

class Texture {
    public:
        Texture ();
        ~Texture();
        bool loadFromFile (SDL_Renderer* rnd, string path);
		bool loadFromText (SDL_Renderer* rnd, TTF_Font* fnt, SDL_Color* cl, string txt);
        void unload();
        void render (int x, int y);
        void render (int x, int y, int w, int h);
        void render (SDL_Rect clip, int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void render (SDL_Rect clip, int x, int y, float scale, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int getWidth();
        int getHeight();

    private:
        SDL_Renderer* renderer;
		TTF_Font* font;
		SDL_Color* color;
		string text;
        SDL_Texture* texture;
        int width;
        int height;
};

#endif
