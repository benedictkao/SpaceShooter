#include "SDLWrapper.h"
#include <SDL_image.h>

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

SDL2::Texture SDL2::loadTexture(const char* path, Renderer renderer) {
	Texture texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, SDL_GetBasePath());

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);

	texture = IMG_LoadTexture(renderer, path);

	if (texture == NULL)
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, IMG_GetError());

	return texture;
}

void SDL2::blit(Texture tex, Renderer renderer, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);	// copies texture width and height to destination
	SDL_RenderCopy(renderer, tex, NULL, &dest);
}

void SDL2::prepareScene(SDL2::Renderer renderer) {
	SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}

void SDL2::presentScene(SDL2::Renderer renderer) {
	SDL_RenderPresent(renderer);
}

Uint64 SDL2::elapsedTimeInMillis() {
	return SDL_GetTicks64();
}

void SDL2::delay(Uint32 timeInMillis) {
	SDL_Delay(timeInMillis);
}

void SDL2::close(SDL2::Window window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}