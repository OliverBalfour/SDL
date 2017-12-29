
#include <iostream>
#include <fstream>

#include "config.hpp"

using std::string;

Config loadConfig (string filename, bool debug) {

	std::ifstream configFile(filename);
	string token;
	Config config;

	if (configFile.is_open()) {
		if (debug) std::cout << std::endl << "Config:" << std::endl;

		while (configFile >> token) {
			if (token == "windowWidth") {
				configFile >> config.windowWidth;
				if (debug) std::cout << "  windowWidth: " << config.windowWidth << std::endl;
			} else if (token == "windowHeight") {
				configFile >> config.windowHeight;
				if (debug) std::cout << "  windowHeight: " << config.windowHeight << std::endl;
			} else if (token == "fullscreen") {
				configFile >> config.fullscreen;
				if (debug) std::cout << "  fullscreen: " << (config.fullscreen ? "on" : "off") << std::endl;
			} else if (token == "fpscounter") {
				configFile >> config.fpscounter;
				if (debug) std::cout << "  fpscounter: " << (config.fpscounter ? "on" : "off") << std::endl;
			} else if (token == "name") {
				configFile >> config.name;
				if (debug) std::cout << "  name: " << config.name << std::endl;
			}
		}

		if (debug) std::cout << std::endl;
	} else {
		std::cerr << "Config error: Config file '" << filename << "' not found. Reverting to default values." << std::endl;
	}

	return config;
}
