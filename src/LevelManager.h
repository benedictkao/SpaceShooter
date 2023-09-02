#pragma once

#include "EnemyManager.h"
#include "EntityManager.h"
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
  EnemyManager      _enemyManager;
  GameStatus        _currentStatus;
  unsigned int      _countdown;
  Level             _currentLevel;

public:
  LevelManager(EntityManager&, PlayerController&, TextureRepo&, TextRenderer&);

  void       initLevel();
  void       reset();
  GameStatus updateStatus();
  GameStatus getStatus() const;

private:
  void setResult(GameStatus);
  void updateLevel();
  void initNextPhase();
};