#pragma once

#include "EntityManager.h"
#include "PlayerController.h"
#include "SDLWrapper.h"
#include "Systems.h"

class SystemManager {
private:
  EntityManager&    _em;
  TextureSystem     _textureSystem;
  PositionSystem    _positionSystem;
  ColliderSystem    _colliderSystem;
  GunSystem         _gunSystem;
  PlayerController& _pControl;

public:
  SystemManager(EntityManager&, TextureRepo&, PlayerController&);

  void setRenderer(SDL2::Renderer);

  void init();
  void update();
};