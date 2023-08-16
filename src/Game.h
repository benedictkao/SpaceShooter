#pragma once

#include "EntityManager.h"
#include "KeyboardManager.h"
#include "SDLWrapper.h"

class Game {
private:
  SDL2::Window   _window;
  SDL2::Renderer _renderer;
  EntityManager  _em;
  bool           _running;

public:
  Game();

  int run();

  void handleEvents(KeyboardManager);

  Uint64 calculateSleepTime(Uint64);
};