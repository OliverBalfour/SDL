
#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

#include "SDL.h"
#include "lib/base64.hpp"

#include "entity.hpp"
#include "entity-controller.hpp"
#include "texture.hpp"

using std::string;

class Map {
    public:
        Map (SDL_Renderer* rnd);
        bool loadFromFile (string name);
        void setPlayer(Entity* pl);
        void render();
    private:
        SDL_Renderer* renderer;
        Entity* player; // pointer to player, also in 'entities'
        std::vector<Entity*> entities;

        unsigned short mapWidth, mapHeight, tileSize, tilesetColumns;
        string tilesetFilename;
        Texture tileset;
        std::vector<uint_least32_t> mapData;
};

#endif
