#pragma once
#include "EnemyManager.h"
#include "PlayerController.h"
#include "TextRenderer.h"
#include "TextureRepo.h"

enum GameStatus { NONE, ONGOING, WIN, LOSE };

class LevelManager {

private:
  PlayerController& _pControl;
  TextureRepo&      _texRepo;
  TextRenderer&     _textRenderer;
  EnemyManager      _enemyManager;
  GameStatus        _currentStatus;
  unsigned int      _lossCountdown;

public:
  LevelManager(EntityManager&, PlayerController&, TextureRepo&, TextRenderer&);

  void       initLevel();
  void       clearLevel();
  GameStatus updateStatus();
  GameStatus getStatus() const;
};