#pragma once

#include "EntityManager.h"
#include "SDLWrapper.h"
#include <unordered_map>

class TextureManager {
public:
  typedef std::unordered_map<TextureKey, SDL2::Texture> TextureMap;

private:
  EntityManager& _em;
  SDL2::Renderer _renderer;
  TextureMap     _textureMap;

public:
  TextureManager(EntityManager&, SDL2::Renderer);
  void          updateTextures();
  SDL2::Texture loadTexture(TextureParams);
  SDL2::Texture loadWithoutCache(const char* path);

private:
  void updateTexture(int entity);
};