
#include <iostream>
#include <SDL.h>
#include "config.hpp"

using std::string;

Config config;
SDL_Window* window = NULL;
SDL_Surface* ctx = NULL;
SDL_Surface* image = NULL;

bool debug = true;
unsigned int timeLast = 0, timeNow = 0;

void drawImage (SDL_Surface* image, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_BlitScaled(image, NULL, ctx, &rect);
}

void render () {
	// Clock
	timeLast = timeNow;
	timeNow = SDL_GetTicks();

	// FPS measurement
	if (config.fpscounter) {
		unsigned int fps;
		// avoid division by zero
		if (timeNow - timeLast <= 1)
		fps = 999;
		else
		fps = 1000 / (timeNow - timeLast);
		std::cout << fps << std::endl;
	}

	SDL_FillRect(ctx, NULL, SDL_MapRGB(ctx->format, 0xFF, 0xFF, 0xFF));
	drawImage(image, 10, 20, 80, 100);
	SDL_UpdateWindowSurface(window);
}

void loop () {
	while (true) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
			if (ev.type == SDL_QUIT || ev.type == SDL_KEYUP && ev.key.keysym.sym == SDLK_ESCAPE)
				return;

		render();
	}
}

SDL_Surface* loadSurface (string path) {
	SDL_Surface* osf = NULL; //optimised surface
	SDL_Surface* sf = SDL_LoadBMP(path.c_str());
	if (sf == NULL) {
		std::cerr << "SDL Error: Could not load image '" << path << "': " << SDL_GetError() << "\n";
		return NULL;
	}
	osf = SDL_ConvertSurface(sf, ctx->format, 0);
	if (osf == NULL) {
		std::cerr << "SDL Error: Could not convert image '" << path << "' from raw: " << SDL_GetError() << "\n";
		return NULL;
	}
	SDL_FreeSurface(sf);
	return osf;
}

void loadResources () {
	image = loadSurface("blob.bmp");
}

void freeResources () {
	SDL_FreeSurface(image);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool init () {
	// Load config file
	config = loadConfig("config.txt", debug);

	// SDL init
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL error: Could not initialse SDL: " << SDL_GetError() << std::endl;
		return false;
	} else if (debug) {
		std::cout << "Initialised SDL\n";
	}

	// Create window
	window = SDL_CreateWindow(
		"Test Application",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		config.windowWidth, config.windowHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
	);
	if (window == NULL) {
		std::cerr << "SDL error: Window could not be created: " << SDL_GetError() << std::endl;
	} else if (debug) {
		std::cout << "Created window\n";
	}

	// Create surface
	ctx = SDL_GetWindowSurface(window);
	if (debug) std::cout << "Created SDL surface (context)\n";

	return true;
}

int main (int argc, char* argv[]) {

	// Initialisation
	if (!init()) {
		std::cerr << "Failed to initialise, crashing\n";
		return 1;
	}

	// Load resources
	if (debug) std::cout << "Loading resources...\n";
	loadResources();
	if (debug) std::cout << "Finished loading resources\n\n";

	// Main loop
	if (debug) std::cout << "Started loop\n";
	loop();
	if (debug) std::cout << "Finished loop\n\n";

	// Free resources (clear memory)
	if (debug) std::cout << "Freeing resources... ";
	freeResources();
	if (debug) std::cout << "done\n\n";

	// It actually worked...
	if (debug) std::cout << "Finished, exiting\n\n";
	return 0;
}
