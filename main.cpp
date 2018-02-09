
#include <iostream>
#include <vector>
#include <sstream>
#include <deque>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "config.hpp"
#include "texture.hpp"
#include "entity.hpp"
#include "player-controller.hpp"
#include "observer.hpp"
#include "input.hpp"
#include "map.hpp"

using std::string;

bool playing = false;

Config config;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
Texture bgTexture;
Texture fpsText;
Texture startText;
Map* map;

std::vector<bool> keys(256);
Mouse mouse = {0, 0, false, false, false};

PlayerController playerController(&keys, &mouse);
Entity* player;
Subject InputEventSubject;

// For FPS averaged over 10 frames
const int frameTimesSize = 10;
std::deque<unsigned int> frameTimes;

void render () {
	SDL_RenderClear(renderer);
	bgTexture.render(0, 0, config.windowWidth, config.windowHeight);
	map->render(window);

	// FPS measurement
	if (config.fpscounter) {
		unsigned int fps;
		// avoid division by zero
		if ((frameTimes.back() - frameTimes.front()) / frameTimesSize <= 1)
			fps = 999;
		else
			fps = 1000 / ((frameTimes.back() - frameTimes.front()) / frameTimesSize);

		SDL_Color color = {0, 0, 0};
		std::stringstream fpsString;
		fpsString << "fps " << fps;
		fpsText.loadFromText(renderer, font, &color, fpsString.str().c_str());
		fpsText.render(10, 10);
	}

	if (!playing)
		startText.render(config.windowWidth / 2, config.windowHeight / 2);

	SDL_RenderPresent(renderer);
}

void loop () {
	while (true) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || ev.type == SDL_KEYUP && ev.key.keysym.sym == SDLK_ESCAPE)
				return;

			if (!playing) {

				if (ev.type == SDL_KEYUP && ev.key.keysym.sym == SDLK_SPACE)
					playing = true;

			} else {

				if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP) {
					unsigned short button;
					switch (ev.button.button) {
						case SDL_BUTTON_LEFT:
						mouse.leftButton = ev.button.state == SDL_PRESSED; button = SDL_BUTTON_LEFT; break;
						case SDL_BUTTON_RIGHT:
						mouse.rightButton = ev.button.state == SDL_PRESSED; button = SDL_BUTTON_RIGHT; break;
						case SDL_BUTTON_MIDDLE:
						mouse.middleButton = ev.button.state == SDL_PRESSED; button = SDL_BUTTON_MIDDLE; break;
					}
					Input input;
					input.button = {(ev.button.state == SDL_PRESSED) ? MOUSEBUTTONDOWN_INPUT : MOUSEBUTTONUP_INPUT, button};
					InputEventSubject.notify(input);
				} else if (ev.type == SDL_MOUSEMOTION) {
					mouse.x = ev.motion.x;
					mouse.y = ev.motion.y;
					Input input;
					input.motion = {MOUSEMOTION_INPUT, ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel};
					InputEventSubject.notify(input);
				} else if (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP) {
					// modifier keys have massive values, presumably buffer underflowed negatives (shift's keycode is 1073742049)
					// so we ignore them to avoid a segfault
					if (ev.key.keysym.sym >= 256)
					continue;
					keys[ev.key.keysym.sym] = ev.key.state == SDL_PRESSED;
					Input input;
					input.key = {(ev.key.state == SDL_PRESSED) ? KEYDOWN_INPUT : KEYUP_INPUT, ev.key.keysym.sym};
					InputEventSubject.notify(input);
				}

			}
		}

		// Clock
		frameTimes.pop_front();
		frameTimes.push_back(SDL_GetTicks());
		// Difference in time between this and last frame, for time based physics
		float delta = (frameTimes[frameTimesSize - 1] - frameTimes[frameTimesSize - 2]) / 1000.0f;

		if (playing)
			map->update(delta);
		render();
	}
}

void loadResources () {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	bgTexture.loadFromFile(renderer, "assets/background.png");
	SDL_Color color = {0, 0, 0};
	startText.loadFromText(renderer, font, &color, "Press Space to start");
	player = new Entity(&playerController, renderer, "assets/sprite.png", font, config.debug);
	map = new Map(renderer);
	map->loadFromFile("levels/test.map");
	map->setPlayer(player);
}

void freeResources () {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool init () {
	// Load config file
	config = loadConfig("config.txt", true);

	// SDL init
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL error: Could not initialse SDL: " << SDL_GetError() << std::endl;
		return false;
	} else if (config.debug) {
		std::cout << "Initialised SDL\n";
	}

	// Create window
	window = SDL_CreateWindow(
		"SDL Game",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		config.windowWidth, config.windowHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
	);
	if (window == nullptr) {
		std::cerr << "SDL error: Window could not be created: " << SDL_GetError() << "\n";
		return false;
	} else if (config.debug) {
		std::cout << "Created window\n";
	}

	// Create renderer
	int rendererFlags = config.vsync ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC : SDL_RENDERER_ACCELERATED;
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	if (renderer == nullptr) {
		std::cerr << "SDL error: Renderer could not be created: " << SDL_GetError() << "\n";
		return false;
	} else if (config.debug) {
		std::cout << "Created renderer\n";
	}

	// Init SDL_image
	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(flags) & flags)) {
		std::cerr << "SDL_image error: Could not initialise: " << IMG_GetError() << "\n";
		return false;
	}

	// Init SDL_ttf
	if (TTF_Init() == -1) {
		std::cerr << "SDL_ttf error: Could not initialise: " << TTF_GetError() << "\n";
		return false;
	}

	// Load font
	font = TTF_OpenFont("assets/DejaVuSans-Bold.ttf", 16);

	// Populate  arrays
	for (int i = 0; i < keys.capacity(); i++)
		keys[i] = false;
	for (int i = 0; i < frameTimesSize; i++)
		frameTimes.push_back(0);
	InputEventSubject.addObserver(&playerController);

	return true;
}

int main (int argc, char* argv[]) {

	// Initialisation
	if (!init()) {
		std::cerr << "Failed to initialise, crashing\n";
		return 1;
	}

	// Load resources
	if (config.debug) std::cout << "Loading resources...\n";
	loadResources();
	if (config.debug) std::cout << "Finished loading resources\n\n";

	// Main loop
	if (config.debug) std::cout << "Started loop\n";
	loop();
	if (config.debug) std::cout << "Finished loop\n\n";

	// Free resources (clear memory)
	if (config.debug) std::cout << "Freeing resources... ";
	freeResources();
	if (config.debug) std::cout << "done\n\n";

	// It actually worked...
	if (config.debug) std::cout << "Finished, exiting\n\n";
	return 0;
}
