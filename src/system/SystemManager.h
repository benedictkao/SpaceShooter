#pragma once

#include "BackgroundManager.h"
#include "EnemyManager.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "MusicManager.h"
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
  MusicManager&     _musicManager;
  BackgroundManager _bgManager;

public:
  SystemManager(EntityManager&,
                TextureRepo&,
                PlayerController&,
                TextRenderer&,
                LevelManager&,
                MusicManager&);

  void init(SDL2::Renderer);
  void update();

private:
  void addDummyPlayer() const;
};