#pragma once

#include "SDLWrapper.h"
#include "KeyboardManager.h"

class Game {
private:
	SDL2::Window _window;
	SDL2::Renderer _renderer;
	bool _running;

public:
	Game();

	int run();

	void handleEvents(KeyboardManager);

	Uint64 calculateSleepTime(Uint64);
};