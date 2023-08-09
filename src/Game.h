#pragma once

#include "SDLWrapper.h"

class Game {
private:
	SDL2::Window _window;
	SDL2::Renderer _renderer;
	bool _running;

public:
	Game();

	int run();

	void handleEvents();

	Uint64 calculateSleepTime(Uint64);
};