#include "SDLWrapper.h"
#include "Constants.h"
#include "SDLWrapper.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

Uint32 SDL2::init() {
  return SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) + TTF_Init() +
         Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
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
  Texture texture = IMG_LoadTexture(renderer, path);

  if (!texture)
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   "Failed to load texture %s. Error: %s",
                   path,
                   IMG_GetError());
  else
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   "Loaded texture %s",
                   path);

  return texture;
}

SDL2::TextureData SDL2::loadText(const char*  text,
                                 const char*  fontPath,
                                 unsigned int size,
                                 const Color& textColor,
                                 Renderer     renderer) {
  TTF_Font*    font        = TTF_OpenFont(fontPath, size);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);

  Texture     tex  = SDL_CreateTextureFromSurface(renderer, textSurface);
  TextureData data = { tex, textSurface->w, textSurface->h };
  SDL_FreeSurface(textSurface);
  return data;
}

SDL2::TextureData SDL2::loadTextWithBackground(const char*  text,
                                         const char*  fontPath,
                                         unsigned int size,
                                         const Color& textColor,
                                         const Color& bgColor,
                                         Renderer renderer) {
  TTF_Font*    font        = TTF_OpenFont(fontPath, size);
  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, text, textColor, bgColor);

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

void SDL2::freeMusic(Music music) {
  Mix_FreeMusic(music);
}

void SDL2::freeSound(Sound sound) {
  Mix_FreeChunk(sound);
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

SDL2::Music SDL2::loadMusic(const char* path) {
  Music music = Mix_LoadMUS(path);
  if (!music)
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   "Failed to load music %s. Error: %s",
                   path,
                   Mix_GetError());
  else
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   "Loaded music %s",
                   path);
  return music;
}

SDL2::Sound SDL2::loadSound(const char* path) {
  Sound sound = Mix_LoadWAV(path);
  if (!sound)
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   "Failed to load sound %s. Error: %s",
                   path,
                   Mix_GetError());
  else
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                   SDL_LOG_PRIORITY_INFO,
                   "Loaded sound %s",
                   path);
  return sound;
}

void SDL2::playMusic(SDL2::Music music) {
  Mix_PlayMusic(music, -1);
}

void SDL2::playSound(SDL2::Sound sound) {
  Mix_PlayChannel(-1, sound, 0);
}

void SDL2::stopMusic() {
  Mix_HaltMusic();
}

void SDL2::stopSounds() {
  Mix_HaltChannel(-1);
}

int SDL2::setMusicVolume(int volume) {
  return Mix_VolumeMusic(volume);
}

int SDL2::setSoundVolume(Sound sound, int volume) {
  return Mix_VolumeChunk(sound, volume);
}

int SDL2::setSoundVolume(int volume) {
  return Mix_Volume(-1, volume);
}

Uint64 SDL2::elapsedTimeInMillis() {
  return SDL_GetTicks64();
}

void SDL2::delay(Uint32 timeInMillis) {
  SDL_Delay(timeInMillis);
}

void SDL2::quit() {
  SDL_Quit();
}

void SDL2::close(SDL2::Window window, SDL2::Renderer renderer) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
}