#pragma once

#include "EnemyManager.h"
#include "EntityManager.h"
#include "KeyboardManager.h"
#include "PlayerController.h"
#include "SDLWrapper.h"
#include "SystemManager.h"
#include "TextureRepo.h"

class Game {
private:
  EntityManager    _em;
  TextureRepo      _texRepo;
  PlayerController _playerController;
  EnemyManager     _enemyManager;
  KeyboardManager  _keyboardManager;
  SystemManager    _systemManager;

public:
  Game();

  int run();

  bool handleEvents(KeyboardManager);

  Uint64 calculateSleepTime(Uint64);
};