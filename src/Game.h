#pragma once

#include "EnemyManager.h"
#include "EntityManager.h"
#include "KeyboardManager.h"
#include "MusicManager.h"
#include "PlayerController.h"
#include "SDLWrapper.h"
#include "SystemManager.h"
#include "TextRenderer.h"
#include "TextureRepo.h"

class Game {
private:
  EntityManager    _em;
  TextureRepo      _texRepo;
  MusicManager     _musicManager;
  PlayerController _playerController;
  TextRenderer     _textRenderer;
  LevelManager     _levelManager;
  KeyboardManager  _keyboardManager;
  SystemManager    _systemManager;

public:
  Game();

  int run();

  bool handleEvents(KeyboardManager);

  Uint64 calculateSleepTime(Uint64);
};