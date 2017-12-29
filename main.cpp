#include <iostream>
#include <SDL.h>
#include "config.hpp"

Config config;
SDL_Window* window;
bool debug = true;
unsigned int timeLast = 0, timeNow = 0;

void loop () {
	while (true) {		
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
	}
}

int main (int argc, char* argv[]) {

	// Load config file
	config = loadConfig("config.txt", debug);

	// SDL init
	SDL_Init(SDL_INIT_VIDEO);
	if (debug) std::cout << "Initialised SDL" << std::endl;

	// Create window
	window = SDL_CreateWindow(
		"Test Application",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		config.windowWidth, config.windowHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);
	if (debug) std::cout << "Created window" << std::endl;

	// // Create context
	// SDL_GLContext context = SDL_GL_CreateContext(window);
	// if (debug) std::cout << "Created SDL OpenGL context (" << getOpenGLVersion() << ")" << std::endl;

	// Main loop
	if (debug) std::cout << "Started loop" << std::endl;
	loop();
	if (debug) std::cout << "Finished loop" << std::endl << std::endl;

	// It actually worked...
	if (debug) std::cout << "Finished, exiting" << std::endl << std::endl;
	return EXIT_SUCCESS;
}
