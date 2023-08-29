#include "SDLWrapper.h"
#include "Constants.h"
#include "SDLWrapper.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

Uint32 SDL2::init() {
  return SDL_Init(SDL_INIT_VIDEO) + TTF_Init();
}

SDL2::Window SDL2::createWindow(const char* title) {
  return SDL_CreateWindow(title,
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          Constants::WINDOW_WIDTH,
                          Constants::WINDOW_HEIGHT,
                          false);
}

SDL2::Renderer SDL2::createRenderer(SDL2::Window window) {
  return SDL_CreateRenderer(window, -1, 0);
}

Uint32 SDL2::pollEvent(SDL2::Event* event) {
  return SDL_PollEvent(event);
}

SDL2::Texture SDL2::loadTexture(const char* path, Renderer renderer) {
  Texture texture;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                 SDL_LOG_PRIORITY_INFO,
                 "Loaded %s",
                 path);

  texture = IMG_LoadTexture(renderer, path);

  if (texture == NULL)
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   IMG_GetError());

  return texture;
}

SDL2::TextureData SDL2::loadText(const char* text, int size, Renderer renderer) {
  // TODO: take this as input
  SDL_Color color = { 204, 204, 0 };
  // TODO: store this somewhere?
  TTF_Font*    font = TTF_OpenFont("../../../res/retro.ttf", size);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);

  Texture     tex  = SDL_CreateTextureFromSurface(renderer, textSurface);
  TextureData data = { tex, textSurface->w, textSurface->h };
  SDL_FreeSurface(textSurface);
  return data;
}

void SDL2::blit(Texture tex, Renderer renderer, const Rect& dest) {
  SDL_RenderCopy(renderer, tex, NULL, &dest);
}

void SDL2::blit(Texture     tex,
                Renderer    renderer,
                const Rect& src,
                const Rect& dest) {
  SDL_RenderCopy(renderer, tex, &src, &dest);
}

void SDL2::destroyTexture(Texture tex) {
  SDL_DestroyTexture(tex);
}

bool SDL2::hasIntersect(const Rect& a, const Rect& b) {
  return static_cast<bool>(SDL_HasIntersection(&a, &b));
}

void SDL2::prepareScene(SDL2::Renderer renderer,
                        Uint8          r,
                        Uint8          g,
                        Uint8          b,
                        Uint8          a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
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