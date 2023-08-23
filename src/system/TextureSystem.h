#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"
#include <unordered_map>

class TextureSystem {
private:
  EntityManager& _em;
  SDL2::Renderer _renderer;

public:
  TextureSystem(EntityManager&);
  void setRenderer(SDL2::Renderer);
  void updateAnimations();
  void updateSprites();

private:
  void updateSprite(int entity);
};