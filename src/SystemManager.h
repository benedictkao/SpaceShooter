#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"
#include "Systems.h"

class SystemManager {
private:
  EntityManager& _em;
  TextureSystem  _textureSystem;
  PositionSystem _positionSystem;
  ColliderSystem _colliderSystem;
  GunSystem      _gunSystem;

public:
  SystemManager(EntityManager&, TextureRepo&);

  void setRenderer(SDL2::Renderer);

  void init();
  void update();
};