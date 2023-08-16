#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"
#include <unordered_map>

class TextureSystem {
public:
  typedef std::unordered_map<TextureKey, SDL2::Texture> TextureMap;

private:
  EntityManager& _em;
  SDL2::Renderer _renderer;

public:
  TextureSystem(EntityManager&);
  void setRenderer(SDL2::Renderer);
  void updateTextures();

private:
  void updateTexture(int entity);
};