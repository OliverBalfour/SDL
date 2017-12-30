
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "config.hpp"
#include "texture.hpp"
#include "entity.hpp"
#include "player-controller.hpp"

using std::string;

Config config;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Texture bgTexture;

PlayerController playerController;
Entity player(playerController, "sprite.png");

bool debug = true;
unsigned int timeLast = 0, timeNow = 0;

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

	SDL_RenderClear(renderer);
	bgTexture.render(0, 0, 1350, 750);
	player.render();
	SDL_RenderPresent(renderer);
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

void loadResources () {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	bgTexture.loadFromFile(renderer, "blob.png");
}

void freeResources () {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
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
		std::cerr << "SDL error: Window could not be created: " << SDL_GetError() << "\n";
		return false;
	} else if (debug) {
		std::cout << "Created window\n";
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		std::cerr << "SDL error: Renderer could not be created: " << SDL_GetError() << "\n";
		return false;
	} else if (debug) {
		std::cout << "Created renderer\n";
	}

	// Init SDL_image
	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(flags) & flags)) {
		std::cerr << "SDL_image error: Could not initialise: " << IMG_GetError() << "\n";
		return false;
	}

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
