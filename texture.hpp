
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

using std::string;

class Texture {
    public:
        Texture ();
        ~Texture();
        bool loadFromFile (SDL_Renderer* rnd, string path);
        void unload();
        void render (int x, int y);
        void render (int x, int y, int w, int h);
        void render (SDL_Rect clip, int x, int y);
        void render (SDL_Rect clip, int x, int y, float scale);
        int getWidth();
        int getHeight();

    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        int width;
        int height;
};

#endif
