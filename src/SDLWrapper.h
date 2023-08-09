#pragma once

#include <SDL.h>

namespace SDL2 {
	typedef SDL_Window* Window;
	typedef SDL_Renderer* Renderer;
	typedef SDL_Texture* Texture;
	typedef SDL_Event Event;

	constexpr auto INIT_SUCCESS{ 0 };

	Uint32 init();

	Window createWindow(const char*);

	Renderer createRenderer(Window);

	Uint32 pollEvent(Event*);

	Texture loadTexture(const char*, Renderer);

	void blit(Texture, Renderer, int x, int y);

	void prepareScene(Renderer);

	void presentScene(Renderer);

	Uint64 elapsedTimeInMillis();

	void delay(Uint32);

	void close(Window);
}