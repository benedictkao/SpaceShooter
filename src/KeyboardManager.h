#pragma once

#include "LevelManager.h"
#include "MusicManager.h"
#include "PlayerController.h"
#include "SDLWrapper.h"

class KeyboardManager {
private:
  PlayerController& _controller;
  LevelManager&     _lvlManager;
  MusicManager&     _musicManager;

public:
  KeyboardManager(PlayerController&, LevelManager&, MusicManager&);

  void handleKeydownEvent(const SDL2::Event&);

  void handleKeyupEvent(const SDL2::Event&);

private:
  void handleLoadScreenKeydownEvent(const SDL2::Event&);
  void handleInGameKeydownEvent(const SDL2::Event&);
  void handlePauseKeydownEvent(const SDL2::Event&);
};