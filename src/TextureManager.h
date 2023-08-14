#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"

class TextureManager {
private:
  EntityManager &_em;
  SDL2::Renderer _renderer;

public:
  TextureManager(EntityManager &, SDL2::Renderer);
  void updateTextures();

private:
  void updateTexture(int entity);
};