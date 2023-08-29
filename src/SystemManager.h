#pragma once

#include "EnemyManager.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "PlayerController.h"
#include "SDLWrapper.h"
#include "Systems.h"
#include "TextRenderer.h"

class SystemManager {
private:
  EntityManager&    _em;
  TextureSystem     _textureSystem;
  PositionSystem    _positionSystem;
  ColliderSystem    _colliderSystem;
  GunSystem         _gunSystem;
  PlayerController& _pControl;
  LevelManager&     _levelManager;

public:
  SystemManager(EntityManager&, TextureRepo&, PlayerController&, TextRenderer&, LevelManager&);

  void init(SDL2::Renderer);
  void update();
};