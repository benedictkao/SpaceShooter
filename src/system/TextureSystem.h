#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"
#include "TextureRepo.h"
#include <unordered_map>

class TextureSystem {
private:
  EntityManager& _em;
  TextureRepo&   _texRepo;
  SDL2::Renderer _renderer;

public:
  TextureSystem(EntityManager&, TextureRepo&);
  void setRenderer(SDL2::Renderer);
  void updateAnimations();
  void updateSprites();

private:
  void updateSprite(int entity);
};