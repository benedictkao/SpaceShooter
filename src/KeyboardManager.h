#pragma once

#include "LevelManager.h"
#include "PlayerController.h"
#include "SDLWrapper.h"

class KeyboardManager {
private:
  PlayerController& _controller;
  LevelManager&     _lvlManager;

public:
  KeyboardManager(PlayerController&, LevelManager&);

  void handleKeydownEvent(const SDL2::Event&);

  void handleKeyupEvent(const SDL2::Event&);

private:
  void handleLoadScreenKeydownEvent(const SDL2::Event&);
  void handleInGameKeydownEvent(const SDL2::Event&);
};