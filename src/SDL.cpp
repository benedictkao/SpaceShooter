#include "SDL.h"

static constexpr auto DEFAULT_WINDOW_WIDTH{ 800 };
static constexpr auto DEFAULT_WINDOW_HEIGHT{ 640 };

Uint32 SDL2::init() {
	return SDL_Init(SDL_INIT_VIDEO);
}

SDL2::Window SDL2::createWindow(const char* title) {
	return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, false);
}

SDL2::Renderer SDL2::createRenderer(SDL2::Window window) {
	return SDL_CreateRenderer(window, -1, 0);
}

Uint32 SDL2::pollEvent(SDL2::Event* event) {
	return SDL_PollEvent(event);
}

Uint64 SDL2::elapsedTimeInMillis(){
	return SDL_GetTicks64();
}

void SDL2::delay(Uint32 timeInMillis) {
	SDL_Delay(timeInMillis);
}

void SDL2::close(SDL2::Window window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}