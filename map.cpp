
#include "map.hpp"

Map::Map (SDL_Renderer* rnd) {
    renderer = rnd;
    entities.reserve(16);
}

bool Map::loadFromFile (string name) {
    std::ifstream mapFile(name);

    if (mapFile.is_open()) {
        // refer to levels/format.txt
        mapFile >> mapWidth;
        mapFile >> mapHeight;
        mapFile >> tilesetFilename;
        mapFile >> tileSize;
        mapFile >> tilesetColumns;

        string data;
        mapFile >> data;
        string rawMapData = base64_decode(data);
        mapData.reserve(mapWidth * mapHeight + 1);

        // Bits on the far end of the 32-bit global tile ID are used for tile flags
        const unsigned int FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
        const unsigned int FLIPPED_VERTICALLY_FLAG   = 0x40000000;
        const unsigned int FLIPPED_DIAGONALLY_FLAG   = 0x20000000;
        unsigned int index = 0;
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                uint_least32_t gid =
                    (int)rawMapData[index] |
                    (int)rawMapData[index + 1] << 8 |
                    (int)rawMapData[index + 2] << 16 |
                    (int)rawMapData[index + 3] << 24;

                index += 4;

                // Read out the flags
                // bool flipped_horizontally = (gid & FLIPPED_HORIZONTALLY_FLAG);
                // bool flipped_vertically = (gid & FLIPPED_VERTICALLY_FLAG);
                // bool flipped_diagonally = (gid & FLIPPED_DIAGONALLY_FLAG);

                // Clear the flags
                gid &=
                    ~(FLIPPED_HORIZONTALLY_FLAG |
                      FLIPPED_VERTICALLY_FLAG |
                      FLIPPED_DIAGONALLY_FLAG);

                mapData.push_back(gid);
            }
        }

        // load tileset
        tilesetFilename = tilesetFilename.substr(3); //remove the '../' from the front
        if (!tileset.loadFromFile(renderer, tilesetFilename)) {
            std::cerr << "Map::loadFromFile error: Could not load tileset file: " << tilesetFilename;
            return false;
        }
    } else {
        std::cerr << "Map::loadFromFile error: Could not find .map file: " << name;
        return false;
    }

    // loop through entities and set their gravity
    for (int i = 0; i < entities.size(); i++) {
        std::cout << "hi";
        entities[i]->control->setGravity(5.0 * tileSize);
    }

    return true;
}

void Map::setPlayer (Entity* pl) {
    player = pl;
    entities.push_back(pl);
    pl->control->setGravity(5.0 * tileSize);
}

bool Map::moveEntity (Entity* ent, double x, double y) {
	EntityController* ctrl = ent->control;

	int nx = (int)round(x + ctrl->x),
		ny = (int)round(y + ctrl->y);

	// check for collisions

	// coordinates of the tile the entity is on
	int ptx = (ctrl->x + ctrl->w / 2) / tileSize, // x, y pos of the tile the entity is located on
		pty = (ctrl->y + ctrl->h / 2) / tileSize, // for optimised collision detection
        psmax = (ctrl->w > ctrl->h ? ctrl->w : ctrl->h) / tileSize;// greater dimension (width/height) in tiles for optimised collision detection

	Box entbox = {nx, ny, ctrl->w, ctrl->h};
	for (int tileY = pty - psmax; tileY < pty + psmax; tileY++) {
		for (int tileX = ptx - psmax; tileX < ptx + psmax; tileX++) {
			if (mapData[tileY * mapWidth + tileX] != 0 && boundingBoxCollision(entbox, {tileX * tileSize, tileY * tileSize, tileSize, tileSize})) {
				if ((x + y) > 1) {
					return moveEntity(ent, x / 2.0, y / 2.0);
				} else {
					return checkEntityForLand(ent);
				}
			}
		}
	}

	// if execution gets to here, there is no collision
	ctrl->x += x;
	ctrl->y += y;

    if (ctrl->state != ENTITY_FLYING && ctrl->state != ENTITY_FLYING_UNCONSCIOUS)
        checkEntityForFall(ent);

	return true;
}

bool Map::checkEntityForFall (Entity* ent) {
    EntityController* ctrl = ent->control;
    int ptx = (ctrl->x + ctrl->w / 2) / tileSize, // x, y pos of the middle/lower tile the entity is located on
        pty = (ctrl->y + ctrl->h / 2) / tileSize;
    bool falling = true;
    // loop through three closest tiles beneath player
    for (int i = ptx - 1; i < ptx + 2; i++) {
        if (
            mapData[(pty + 1) * mapWidth + i] != 0 &&
            ctrl->x < (i + 1) * tileSize &&
            ctrl->x + tileSize > i * tileSize
        ) {
            falling = false;
            break;
        }
    }
    if (falling) {
        ctrl->vy = 0;
		// vx stays equal to running speed
        ctrl->state = ENTITY_FLYING;
    }
	return falling;
}

bool Map::checkEntityForLand (Entity* ent) {
	EntityController* ctrl = ent->control;
	bool landed = ((int)round(ctrl->y) % tileSize) == 0 && !checkEntityForFall(ent);
	if (landed) {
		ctrl->state = ENTITY_IDLE;
		ctrl->vy = 0;
	}
	return landed;
}

void Map::update (float delta) {
	for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(delta);
		moveEntity(entities[i], entities[i]->control->dx, entities[i]->control->dy);
		entities[i]->control->dx = 0;
		entities[i]->control->dy = 0;
    }
}

void Map::render (SDL_Window* window) {
    int wwidth, wheight;
    SDL_GetWindowSize(window, &wwidth, &wheight);
	Box box = player->getBoundingBox();
    int ox, oy; // offset x and y, to make the camera follow the player
    ox = -( (int)round(player->control->x) ) + (wwidth  - box.w) / 2;
    oy = -( (int)round(player->control->y) ) + (wheight - box.h) / 2;

    // render tiles
    unsigned int index, tx, ty;
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {

            index = mapData[y * mapWidth + x];
            if (index == 0)
                continue;
            index--;
            tx = index % tilesetColumns;
            ty = index / tilesetColumns; // int division

            tileset.render({ (int)(tx * tileSize), (int)(ty * tileSize), tileSize, tileSize }, x * tileSize + ox, y * tileSize + oy);


        }
    }

    // render entities (incl. player)
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->render(ox, oy);
    }
}
