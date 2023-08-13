#pragma once

#include "PlayerController.h"
#include "SDLWrapper.h"

class KeyboardManager {
private:
  PlayerController &_controller;

public:
  KeyboardManager(PlayerController &);

  void handleKeydownEvent(const SDL2::Event &);

  void handleKeyupEvent(const SDL2::Event &);
};