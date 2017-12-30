
#ifndef CONFIG_H
#define CONFIG_H

using std::string;

struct Config {
	int windowWidth =	800;
	int windowHeight =	600;
	bool fullscreen =	false;
	bool fpscounter =	false;
	bool vsync =		true;
	string name =		"SDL Game";
};

Config loadConfig (string filename, bool debug = false);

#endif
