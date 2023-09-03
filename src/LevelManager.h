#pragma once

#include "EnemyManager.h"
#include "EntityManager.h"
#include "MusicManager.h"
#include "PlayerController.h"
#include "TextRenderer.h"
#include "TextureRepo.h"
#include "level/Level.h"
#include <vector>

enum GameStatus { NONE, ONGOING, WIN, LOSE };

class LevelManager {

private:
  EntityManager&    _em;
  PlayerController& _pControl;
  TextureRepo&      _texRepo;
  TextRenderer&     _textRenderer;
  MusicManager&     _musicManager;
  EnemyManager      _enemyManager;
  GameStatus        _currentStatus;
  unsigned int      _countdown;
  Level             _currentLevel;

public:
  LevelManager(EntityManager&,
               PlayerController&,
               TextureRepo&,
               TextRenderer&,
               MusicManager&);

  void       initLevel();
  void       reset();
  GameStatus updateStatus();
  GameStatus getStatus() const;

private:
  void setResult(GameStatus);
  void displayResult(const char* title, const char* subtitle, unsigned int soundId);
  void updateLevel();
  void initNextPhase();
};