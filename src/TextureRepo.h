#pragma once

#include "Components.h"
#include "SDLWrapper.h"
#include <unordered_map>

class TextureRepo {
public:
  typedef std::unordered_map<TextureKey, SDL2::Texture> TextureMap;

private:
  SDL2::Renderer _renderer;
  TextureMap _textureMap;

public:
  void          setRenderer(SDL2::Renderer);
  SDL2::Texture loadTexture(TextureParams);
  SDL2::Texture loadWithoutCache(const char* path);
};