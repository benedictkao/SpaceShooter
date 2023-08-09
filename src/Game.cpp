#include "Game.h"

static constexpr auto TARGET_FPS{ 30 };
static constexpr auto MILLIS_PER_FRAME{ 1000 / TARGET_FPS };
enum GAME_INIT_ERROR { SUBSYSTEM = 1, WINDOW, RENDERER };

static inline Uint64 max(Uint64 a, Uint64 b) noexcept {
	return a > b ? a : b;
}

Game::Game() : _window(nullptr), _renderer(nullptr), _running(false) {}

int Game::run() {
	const int initResult = SDL2::init();
	if (initResult != SDL2::INIT_SUCCESS)
		return GAME_INIT_ERROR::SUBSYSTEM;

	_window = SDL2::createWindow("Jump!");
	if (!_window)
		return GAME_INIT_ERROR::WINDOW;

	_renderer = SDL2::createRenderer(_window);
	if (!_renderer)
		return GAME_INIT_ERROR::RENDERER;

	_running = true;
	while (_running) {
		// main game loop

		Uint64 frameStart = SDL2::elapsedTimeInMillis();

		handleEvents();
		
		// calculations

		// ui render

		Uint64 sleepTime = calculateSleepTime(frameStart);
		SDL2::delay(sleepTime);
	}

	SDL2::close(_window);
	return 0;
}

void Game::handleEvents() {
	SDL2::Event event;
	while (SDL2::pollEvent(&event)) {
		switch (event.type) {	// add other events below here
		case SDL_QUIT:
			_running = false;
			break;
		default:
			break;
		}
	}
}

Uint64 Game::calculateSleepTime(Uint64 frameStart) {
	Uint64 actualFrameTime = frameStart - SDL2::elapsedTimeInMillis();
	Uint64 sleepTime = max(MILLIS_PER_FRAME - actualFrameTime, 0);
	return sleepTime;
}